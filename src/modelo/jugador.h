
#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <set>


class Jugador {

int id_;
int partidosJugados_;
int puntos_;
bool disponible_;
bool enPredio_;
std::set<int> parejas_;

public:
  Jugador(int id);
  int getId() const;

  void agregarPartido(int idJugador);
  bool puedeJugarCon(int idJugador) const;
  int getPartidosJugados() const;

  bool disponible() const;
  void setDisponible(bool disponible);

  void addPuntos(int puntos);
  int getPuntos() const;

  void entrarPredio();
  void salirPredio();
  bool estaEnPredio();

};


#endif // __JUGADOR_H__
