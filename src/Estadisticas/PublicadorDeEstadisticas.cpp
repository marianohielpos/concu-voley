//
// Created by rafael on 17/09/17.
//

#include <iostream>
#include "PublicadorDeEstadisticas.h"

PublicadorDeEstadisticas::PublicadorDeEstadisticas(const unsigned maxCantidadResultados,
                        const unsigned maxCantidadJugadores) throw(std::exception) :
                        lockResultados(maxCantidadResultados),
                        lockJugadores(maxCantidadJugadores){
}

PublicadorDeEstadisticas::~PublicadorDeEstadisticas() {
}

void PublicadorDeEstadisticas::update() {
    std::list<TResultadoSerializado>* listaResultados=this->lockResultados.readAll();
    std::list<TJugadorPuntaje>* listaJugadores=this->lockJugadores.readAll();
    publicador.update(listaResultados,listaJugadores);
    delete(listaResultados);
    delete(listaJugadores);
}