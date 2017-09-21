
#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <set>


class Jugador {

int id_;
int partidosJugados_;
bool disponible_;
std::set<int> parejas_;

public:
  Jugador(int id);
  int getId() const;

  void agregarPartido(int idJugador);
  bool puedeJugarCon(int idJugador) const;
  int getPartidosJugados() const;

  bool disponible() const;
  void setDisponible(bool disponible);

};


#endif // __JUGADOR_H__
