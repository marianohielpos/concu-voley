//
// Created by rafael on 18/09/17.
//

#include <iostream>
#include "ConexionPubEstad.h"
#include "PublicadorDeEstadisticas.h"

ConexionPubEstad::ConexionPubEstad(unsigned int maxCantidadResultados, unsigned int maxCantidadJugadoresPuntaje)
                                    throw(std::exception){
    memoriaCompartidaResultados=new MemoriaCompartidaResultados(maxCantidadResultados);
    lockMemoriaCompartidaResultados=new LockMemoriaCompartidaResultados(memoriaCompartidaResultados);
    lockMemoriaCompartidaResultados->cleanMemoria();

    memoriaCompartidaJugadores=new MemoriaCompartidaJugadores(maxCantidadJugadoresPuntaje);
    lockMemoriaCompartidaJugadores=new LockMemoriaCompartidaJugadores(memoriaCompartidaJugadores);
    lockMemoriaCompartidaJugadores->cleanMemoria();
}

ConexionPubEstad::~ConexionPubEstad() {
    delete(this->memoriaCompartidaResultados);
    delete(this->lockMemoriaCompartidaResultados);
    memoriaCompartidaResultados=NULL;
    lockMemoriaCompartidaResultados=NULL;

    delete(this->memoriaCompartidaJugadores);
    delete(this->lockMemoriaCompartidaJugadores);
    memoriaCompartidaJugadores=NULL;
    lockMemoriaCompartidaJugadores=NULL;
}

bool ConexionPubEstad::addResultado(TResultadoSerializado &resultadoSerializado) {
    return this->lockMemoriaCompartidaResultados->push(resultadoSerializado);
}

bool ConexionPubEstad::addJugadorPuntaje(TJugadorPuntaje &jugadorPuntaje) {
    return this->lockMemoriaCompartidaJugadores->push(jugadorPuntaje);
}