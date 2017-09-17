
#include <iostream>
#include <sys/wait.h>
#include "torneo.h"

Torneo::Torneo(std::vector<Jugador> jugadoresIniciales) : jugadores(jugadoresIniciales) {
}

void Torneo::run() {
  std::cout << "Torneo corriendo!" << std::endl;

  while(sePuedeArmarPartido() || partidosCorriendo()) {
      if (lanzarPartido()) {
        continue;
      }
      int status = 0;
      wait(&status);
  }
}

bool Torneo::sePuedeArmarPartido() {
  return false;
};

bool Torneo::partidosCorriendo() {
  return false;
};

bool Torneo::lanzarPartido() {
  return false;
};
