
#include "jugador.h"

Jugador::Jugador(int id) : id_(id) {
}

void Jugador::agregarPartido(int idJugador){
  parejas.insert(idJugador);
  partidosJugados_++;
};

bool Jugador::puedeJugarCon(int idJugador){
  return parejas.find(idJugador) == parejas.end();
};

int Jugador::getPartidosJugados(){
  return partidosJugados_;
};

