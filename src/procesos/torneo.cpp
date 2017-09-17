
#include <iostream>
#include "torneo.h"

Torneo::Torneo(std::vector<Jugador> jugadoresIniciales) : jugadores(jugadoresIniciales) {
}

void Torneo::run() {
  std::cout << "Torneo corriendo!" << std::endl;
}
