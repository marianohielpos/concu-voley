
#ifndef __TORNEO_H__
#define __TORNEO_H__

#include <vector>
#include <map>
#include "../utils/Opciones.h"
#include "../ipc/EventHandler.h"
#include "../modelo/jugador.h"
#include "../Estadisticas/ConexionPubEstad.h"
#include "../MemoriaCompartida/LockMemoriaCompartidaCanchas.h"
#include "../MemoriaCompartida/Serializados.h"
#include "partido.h"
#include "../Semaforo/Semaforo.h"

#define JUGADORES_PARA_TORNEO 10



class Torneo {

  Opciones opts_;
  std::vector<Jugador> jugadores_;
  std::map<pid_t, Partido> partidos_;
  ConexionPubEstad conexion_;
  LockMemoriaCompartidaCanchas memoriaCanchas_;
    Semaforo semaforo = Semaforo("principal.cpp",0);

  bool sePuedeArmarPartido();
  bool partidosCorriendo();
  bool lanzarPartido();
  bool siguientesParticipantes(participantes& p);
  void finalizarPartido(pid_t pidPartido, int status);
  void guardarResultado(pid_t pidPartido, int status);
  void liberarCancha(pid_t pidPartido);
  void finalizarTorneo();
  void liberarRecursos();
  void checkearSalidaJugadores();
  void checkearEntradaJugadores();
    void esperarParticipantes() const;

public:
  Torneo(Opciones opts);
  void agregarJugador();

  void run();
  //~Torneo();
};


class ReceptorDeJugadores : public EventHandler {

Torneo& t_;

public:
  ReceptorDeJugadores(Torneo& t);

  virtual int handleSignal (int signum);

  ~ReceptorDeJugadores();
};

#endif
