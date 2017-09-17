
#include <iostream>
#include <unistd.h>
#include "torneo.h"

Torneo::Torneo(std::vector<Jugador> jugadoresIniciales) : jugadores_(jugadoresIniciales) {
}

void Torneo::run() {
  std::cout << "Torneo corriendo!" << std::endl;

  while(sePuedeArmarPartido() || partidosCorriendo()) {
      if (lanzarPartido()) {
        continue;
      }
      int status = 0;
      pid_t pidPartido = wait(&status);

      partidos_.erase(pidPartido);
  }
}


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

  Partido partido(p);
  pid_t pidPartido = fork();
  if (pidPartido == 0) {
    partido.run();
  } else {
    partidos_.insert({pidPartido, partido});
  }
  return true;
};
