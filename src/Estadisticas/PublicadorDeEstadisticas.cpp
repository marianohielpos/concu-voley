//
// Created by rafael on 17/09/17.
//

#include <iostream>
#include "PublicadorDeEstadisticas.h"
#include "Serializados.h"

PublicadorDeEstadisticas::PublicadorDeEstadisticas(const unsigned maxCantidadResultados,
                                                   const unsigned maxCantidadJugadores)
                                                    throw(std::exception){
    this->memoriaResultados=new MemoriaCompartidaResultados(maxCantidadResultados);
    this->lockResultados=new LockMemoriaCompartidaResultados(memoriaResultados);

    this->memoriaJugadores=new MemoriaCompartidaJugadores(maxCantidadJugadores);
    this->lockJugadores=new LockMemoriaCompartidaJugadores(memoriaJugadores);
}

PublicadorDeEstadisticas::~PublicadorDeEstadisticas() {
    delete(memoriaResultados);
    delete(lockResultados);
    memoriaResultados=NULL;
    lockResultados=NULL;

    delete(memoriaJugadores);
    delete(lockJugadores);
    memoriaJugadores=NULL;
    lockJugadores=NULL;
}

void PublicadorDeEstadisticas::update() {
    std::list<TResultadoSerializado>* listaResultados=this->lockResultados->readAll();
    std::list<TJugadorPuntaje>* listaJugadores=this->lockJugadores->readAll();
    publicador.update(listaResultados,listaJugadores);

    delete(listaResultados);
    delete(listaJugadores);
}