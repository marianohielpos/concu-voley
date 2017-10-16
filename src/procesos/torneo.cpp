
#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <Logger.h>
#include "torneo.h"
#include "../ipc/SignalHandler.h"
#include "../ipc/SIGINT_Handler.h"
#include "../MemoriaCompartida/Serializados.h"
#include <sstream>
#include <algorithm>
#include <Opciones.h>


Torneo::Torneo( Opciones opts) : opts_(opts), conexion_(opts_.jugadores * opts_.partidos,
                                 opts_.jugadores), memoriaCanchas_(opts_),
                                 memoriaCompartidaPersonas(opts.jugadores,opts.capacidad) {
  this->inicializarVectorJugadores(opts_.jugadores);
}

void Torneo::run() {
  Logger::getInstance()->info("[Torneo] Torneo corriendo!");
  SIGINT_Handler sigint_handler;
  SignalHandler :: getInstance()->registrarHandler (SIGINT, &sigint_handler);
  /*
  while((this->memoriaCompartidaPersonas.cantidadEnPredio()<JUGADORES_PARA_TORNEO)&&
          (sigint_handler.getGracefulQuit() == 0)){
    Logger::getInstance()->info("[Torneo] No hay jugadores suficientes!");
  }*/
  while(sigint_handler.getGracefulQuit() == 0 &&
        (sePuedeArmarPartido() || partidosCorriendo())) {
      if (lanzarPartido()) {
        continue;
      }
      int status = 0;
      pid_t pidPartido = wait(&status);
      if (pidPartido != -1) {
        if (WIFEXITED(status)) {
          Logger::getInstance()->info("[Torneo] Partido terminó exitosamente " + std::to_string(pidPartido));
          finalizarPartido(pidPartido, status);
        } else {
          Logger::getInstance()->info("[Torneo] Partido terminó por una interrupción");
          liberarCancha(pidPartido);
        }
      } else {
        Logger::getInstance()->info("[Torneo] Wait terminó sin exit!");
      }
  }
  Logger::getInstance()->info("[Torneo] Escribiendo los resultados!");
  if (sigint_handler.getGracefulQuit() == 0) {
    Logger::getInstance()->info("[Torneo] Escribiendo los resultados!");
    finalizarTorneo();
  } else {
    Logger::getInstance()->info("[Torneo] Recibí SIGINT! Liberando recursos.");
    liberarRecursos();
  }
}


void Torneo::finalizarPartido(pid_t pidPartido, int status) {
  guardarResultado(pidPartido, status);
  Partido p = partidos_.at(pidPartido);
  participantes parts = p.getParticipantes();

  for (int i = 0; i < 4; ++i) {
    Jugador& j = jugadores_.at(parts[i]);
    int offset = (i % 2 == 0) ? 1 : -1;
    j.agregarPartido(parts[i + offset]);
  }
  this->memoriaCompartidaPersonas.marcarComoEsperandoJugar(parts);
  liberarCancha(pidPartido);
}

void Torneo::liberarCancha(pid_t pidPartido) {
  Partido p = partidos_.at(pidPartido);
  participantes parts = p.getParticipantes();

  for (int i = 0; i < 4; ++i) {
    Jugador& j = jugadores_.at(parts[i]);
    if (j.getPartidosJugados() <= opts_.partidos) {
      j.setDisponible(true);
    }
  }

  TCanchaSerializada cancha = p.getCancha();

  memoriaCanchas_.leer(cancha, cancha.fila, cancha.columna);
  cancha.proceso = 0;
  cancha.ocupada = false;
  memoriaCanchas_.escribir(cancha);

  partidos_.erase(pidPartido);
}


void Torneo::guardarResultado(pid_t pidPartido, int status) {

  Partido p = partidos_.at(pidPartido);
  participantes parts = p.getParticipantes();
  int resultadoPareja1 = 0, resultadoPareja2 = 0;

  switch (WEXITSTATUS(status)) {
      case PRIMER_PAREJA_3: resultadoPareja1 = 3; break;
      case PRIMER_PAREJA_2: resultadoPareja1 = 2; resultadoPareja2 = 1; break;
      case SEGUNDA_PAREJA_2: resultadoPareja1 = 1; resultadoPareja2 = 2; break;
      case SEGUNDA_PAREJA_3: resultadoPareja2 = 3; break;
  }

  for (int i = 0; i < 4; ++i) {
    Jugador& j = jugadores_.at(parts[i]);
    j.addPuntos((i < 2) ? resultadoPareja1 : resultadoPareja2);
  }

  TResultadoSerializado res;
  res.init(parts[0], parts[1], parts[2], parts[3], resultadoPareja1, resultadoPareja2);

  conexion_.addResultado(res);

  std::stringstream ss;
  ss << "[Torneo] [Resultados del partido " << pidPartido << "] Jugadores "
     << parts[0] << " y " << parts[1]  << ": "  << resultadoPareja1  << " puntos; "
     << parts[2] << " y " << parts[3] << ": " << resultadoPareja2 << " puntos;";

  Logger::getInstance()->info(ss.str());

};

bool Torneo::siguientesParticipantes(participantes& p) {
  return this->memoriaCompartidaPersonas.obtenerParticipantes(p,this->partidos_);
};

bool Torneo::sePuedeArmarPartido() {
  return this->memoriaCompartidaPersonas.sePuedenObtenerParticipantes(this->partidos_);
};

bool Torneo::partidosCorriendo() {
  return !partidos_.empty();
};

bool Torneo::lanzarPartido() {
  participantes p;
  bool res = siguientesParticipantes(p);
  if (!res) {
    return false;
  }

  for (int i = 0; i < 4; ++i) {
    Jugador& j = jugadores_.at(p[i]);
    j.setDisponible(false);
  }

  TCanchaSerializada cancha;
  memoriaCanchas_.obtenerCanchaLibre(cancha);

  Partido partido(p, this->opts_, cancha);
  pid_t pidPartido = fork();
  if (pidPartido == 0) {
    partido.run();
  } else {
    cancha.ocupada = true;
    cancha.proceso = pidPartido;
    memoriaCanchas_.escribir(cancha);
    partidos_.insert({pidPartido, partido});
  }

  std::stringstream ss;
  ss << "[Torneo] Torneo: lanzando partido " << pidPartido << " en la cancha fila "
     << cancha.fila << " y columna " << cancha.columna;

  Logger::getInstance()->info(ss.str());

  return true;
};

bool compararPuntajes(Jugador const& j1, Jugador const& j2) {
    return j1.getPuntos() > j2.getPuntos();
}


void Torneo::finalizarTorneo() {
  std::sort(std::begin(jugadores_), std::end(jugadores_), compararPuntajes);

  for (Jugador const& j : jugadores_) {
    TJugadorPuntaje punt;
    punt.jugador = j.getId();
    punt.puntaje = j.getPuntos();

    std::stringstream ss;
    ss << "[Torneo] El jugador " << j.getId() << " obtuvo " << j.getPuntos() << " puntos!";
    Logger::getInstance()->info(ss.str());

    conexion_.addJugadorPuntaje(punt);
  }

  liberarRecursos();
};

void Torneo::liberarRecursos() {
  for (auto const& pair : partidos_) {
    kill(pair.first, SIGINT);
  }

  for (auto const& element : partidos_) {
    wait(NULL);
  }
  memoriaCanchas_.liberar();
  conexion_.liberarRecursos();
  memoriaCompartidaPersonas.liberarRecursos();
};

void Torneo::inicializarVectorJugadores(unsigned int maxCantPersonas) {
  for(unsigned int i=0;i<maxCantPersonas;i++){
    Jugador jugador(i);
    this->jugadores_.push_back(jugador);
  }
}