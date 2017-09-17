
#ifndef __TORNEO_H__
#define __TORNEO_H__

#include <vector>
#include "../modelo/jugador.h"

#define JUGADORES_PARA_TORNEO 10

class Torneo {

  std::vector<Jugador> jugadores;

  bool sePuedeArmarPartido();
  bool partidosCorriendo();
  bool lanzarPartido();


public:
  Torneo(std::vector<Jugador> jugadoresIniciales);

  void run();
  //~Torneo();

};

#endif
