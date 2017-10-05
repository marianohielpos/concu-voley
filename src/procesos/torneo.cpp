
#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <Logger.h>
#include "torneo.h"
#include "../ipc/SignalHandler.h"
#include "../MemoriaCompartida/Serializados.h"
#include <sstream>

Torneo::Torneo(std::vector<Jugador> jugadoresIniciales, Opciones opts, Logger* logger)
  : jugadores_(jugadoresIniciales), opts_(opts),
    conexion_(opts_.jugadores * opts_.partidos, opts_.jugadores) {

  this->logger = logger;
}

void Torneo::run() {

  this->logger->info("Torneo corriendo!");

  ReceptorDeJugadores sigusr_handler(*this);
  SignalHandler :: getInstance()->registrarHandler (SIGUSR1, &sigusr_handler);

  while(sePuedeArmarPartido() || partidosCorriendo()) {
      if (lanzarPartido()) {
        continue;
      }
      int status = 0;
      pid_t pidPartido = wait(&status);

      if (pidPartido != -1 && WIFEXITED(status)) {
        finalizarPartido(pidPartido, status);
      } else {
        this->logger->info("Wait terminó sin exit!");
      }

  }
}


void Torneo::finalizarPartido(pid_t pidPartido, int status) {
  imprimirResultado(pidPartido, status);

  Partido p = partidos_.at(pidPartido);
  participantes parts = p.getParticipantes();

  for (int i = 0; i < 4; ++i) {
    Jugador& j = jugadores_.at(parts[i]);
    int offset = (i % 2 == 0) ? 1 : -1;
    j.agregarPartido(parts[i + offset]);
    if (j.getPartidosJugados() <= opts_.partidos) {
      j.setDisponible(true);
    }
  }

  partidos_.erase(pidPartido);
}


void Torneo::imprimirResultado(pid_t pidPartido, int status) {

  Partido p = partidos_.at(pidPartido);
  participantes parts = p.getParticipantes();
  int resultadoPareja1 = 0, resultadoPareja2 = 0;

  switch (WEXITSTATUS(status)) {
      case PRIMER_PAREJA_3: resultadoPareja1 = 3; break;
      case PRIMER_PAREJA_2: resultadoPareja1 = 2; resultadoPareja2 = 1; break;
      case SEGUNDA_PAREJA_2: resultadoPareja1 = 1; resultadoPareja2 = 2; break;
      case SEGUNDA_PAREJA_3: resultadoPareja2 = 3; break;
  }

  std::stringstream ss;

  TResultadoSerializado res;
  unsigned int resultadoSetsEquipo1[5];
  unsigned int resultadoSetsEquipo2[5];
  for(int set=0; set < 5; set++){
      resultadoSetsEquipo1[set] = 1;
      resultadoSetsEquipo2[set] = 1;
  }
  res.init(1, 1, parts.data(), &parts.data()[2], 5, resultadoSetsEquipo1,resultadoSetsEquipo2);

  conexion_.addResultado(res);

  ss << "[Resultados del partido " << pidPartido << "] Jugadores "
     << parts[0] << " y " << parts[1]  << ": "  << resultadoPareja1  << " puntos; "
     << parts[2] << " y " << parts[3] << ": " << resultadoPareja2 << " puntos;";

  this->logger->info(ss.str());

};


bool Torneo::siguientesParticipantes(participantes& p) {

  bool parEncontrado;

  for (int i = 0; i < 2; i++) {
    parEncontrado = false;
    for (Jugador const& j1 : jugadores_) {
      if (j1.disponible()) {

        if (i > 0 && (p[0] == j1.getId() || p[1] == j1.getId())) {
          // Si estoy buscando el segundo par de jugadores, me fijo que no lo haya
          // incluido en el primer par
          continue;
        }

        for (Jugador const& j2 : jugadores_) {
          if ((&j1 != &j2) && j2.disponible() && j1.puedeJugarCon(j2.getId())) {

            if (i > 0 && (p[0] == j2.getId() || p[1] == j2.getId())) {
              continue;
            }

            p[0 + i * 2] = j1.getId();
            p[1 + i * 2] = j2.getId();
            parEncontrado = true;
            break;
          }
        }
      }
      if (parEncontrado) {
        break;
      }
    }
    if (!parEncontrado) {
      break;
    }
  }

  return parEncontrado;
};

bool Torneo::sePuedeArmarPartido() {
  participantes p {-1, -1, -1, -1};
  return siguientesParticipantes(p);
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

  Partido partido(p, logger, this->opts_);
  pid_t pidPartido = fork();
  if (pidPartido == 0) {
    partido.run();
  } else {
    partidos_.insert({pidPartido, partido});
  }
  return true;
};

void Torneo::agregarJugador() {
  Jugador j(jugadores_.size());
  jugadores_.push_back(j);
};



ReceptorDeJugadores::ReceptorDeJugadores(Torneo& t) : t_(t) {
};

ReceptorDeJugadores::~ReceptorDeJugadores() {
};

int ReceptorDeJugadores::handleSignal (int signum) {
  assert(signum == SIGUSR1);
  t_.agregarJugador();
  return 0;
}
