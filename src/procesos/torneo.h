
#ifndef __TORNEO_H__
#define __TORNEO_H__

#include <vector>
#include <map>
#include "../utils/Opciones.h"
#include "../ipc/EventHandler.h"
#include "../modelo/jugador.h"
#include "partido.h"

#define JUGADORES_PARA_TORNEO 10



class Torneo {

  Opciones opts_;
  std::vector<Jugador> jugadores_;
  std::map<pid_t, Partido> partidos_;

  bool sePuedeArmarPartido();
  bool partidosCorriendo();
  bool lanzarPartido();
  bool siguientesParticipantes(participantes& p);
  void finalizarPartido(pid_t pidPartido, int status);
  void imprimirResultado(pid_t pidPartido, int status);


public:
  Torneo(std::vector<Jugador> jugadoresIniciales, Opciones opts);
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
