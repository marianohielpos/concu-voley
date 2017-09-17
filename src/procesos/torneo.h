
#ifndef __TORNEO_H__
#define __TORNEO_H__

#include <vector>
#include <map>
#include "../modelo/jugador.h"
#include "partido.h"

#define JUGADORES_PARA_TORNEO 10



class Torneo {

  std::vector<Jugador> jugadores_;
  std::map<pid_t, Partido> partidos_;

  bool sePuedeArmarPartido();
  bool partidosCorriendo();
  bool lanzarPartido();
  bool siguientesParticipantes(participantes& p);

public:
  Torneo(std::vector<Jugador> jugadoresIniciales);

  void run();
  //~Torneo();

};

#endif
