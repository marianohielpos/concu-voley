//
// Created by rafael on 17/09/17.
//

#include <iostream>
#include "PublicadorDeEstadisticas.h"
#include "Serializados.h"

PublicadorDeEstadisticas::PublicadorDeEstadisticas(const unsigned maxCantidadResultados,
                                                   const unsigned maxCantidadJugadores)
                                                    throw(std::exception){
    this->lockResultados=new LockMemoriaCompartidaResultados(maxCantidadResultados);
    this->lockJugadores=new LockMemoriaCompartidaJugadores(maxCantidadJugadores);
}

PublicadorDeEstadisticas::~PublicadorDeEstadisticas() {
    delete(lockResultados);
    lockResultados=NULL;
    delete(lockJugadores);
    lockJugadores=NULL;
}

void PublicadorDeEstadisticas::update() {
    std::list<TResultadoSerializado>* listaResultados=this->lockResultados->readAll();
    std::list<TJugadorPuntaje>* listaJugadores=this->lockJugadores->readAll();
    publicador.update(listaResultados,listaJugadores);
    delete(listaResultados);
    delete(listaJugadores);
}