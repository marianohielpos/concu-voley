
#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <set>


class Jugador {

int id_;
int partidosJugados_;
std::set<int> parejas;

public:
  Jugador(int id);
  void agregarPartido(int idJugador);
  bool puedeJugarCon(int idJugador);
  int getPartidosJugados();

};


#endif // __JUGADOR_H__
