
#include "jugador.h"

Jugador::Jugador(int id) : id_(id), partidosJugados_(0),
                           disponible_(true), enPredio_(true), puntos_(0) {
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
  return enPredio_ && disponible_;
};

void Jugador::setDisponible(bool disponible) {
  disponible_ = disponible;
};


void Jugador::entrarPredio() {
  enPredio_ = true;
};

void Jugador::salirPredio() {
  enPredio_ = false;
};

bool Jugador::estaEnPredio() {
  return enPredio_;
};

void Jugador::addPuntos(int puntos) {
  puntos_ += puntos;
};

int Jugador::getPuntos() const {
  return puntos_;
};

