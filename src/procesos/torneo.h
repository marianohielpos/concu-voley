
#ifndef __TORNEO_H__
#define __TORNEO_H__

#include <vector>
#include "../modelo/jugador.h"

class Torneo {

  std::vector<Jugador> jugadores;

public:
  Torneo(std::vector<Jugador> jugadoresIniciales);

  void run();
  //~Torneo();

};

#endif
