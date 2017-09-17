
#include "jugador.h"

Jugador::Jugador(int id) : id_(id), partidosJugados_(0), disponible_(true) {
}

int Jugador::getId() const {
  return id_;
}

void Jugador::agregarPartido(int idJugador) {
  parejas_.insert(idJugador);
  partidosJugados_++;
};

bool Jugador::puedeJugarCon(int idJugador) const {
  return parejas_.find(idJugador) == parejas_.end();
};

int Jugador::getPartidosJugados() const {
  return partidosJugados_;
};


bool Jugador::disponible() const {
  return disponible_;
};

void Jugador::setDisponible(bool disponible) {
  disponible_ = disponible;
};

