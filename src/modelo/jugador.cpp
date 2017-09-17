
#include "jugador.h"

Jugador::Jugador(int id) : id_(id), partidosJugados_(0), disponible_(true) {
}

void Jugador::agregarPartido(int idJugador){
  parejas_.insert(idJugador);
  partidosJugados_++;
};

bool Jugador::puedeJugarCon(int idJugador){
  return parejas_.find(idJugador) == parejas_.end();
};

int Jugador::getPartidosJugados(){
  return partidosJugados_;
};


bool Jugador::disponible() {
  return disponible_;
};

void Jugador::setDisponible(bool disponible) {
  disponible_ = disponible;
};

