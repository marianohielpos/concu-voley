//
// Created by rafael on 18/09/17.
//

#include <iostream>
#include "ConexionPubEstad.h"
#include "PublicadorDeEstadisticas.h"

ConexionPubEstad::ConexionPubEstad(unsigned int maxCantidadResultados, unsigned int maxCantidadJugadoresPuntaje)
                                    throw(std::exception){
    lockMemoriaCompartidaResultados=new LockMemoriaCompartidaResultados(maxCantidadResultados);
    lockMemoriaCompartidaResultados->cleanMemoria();
    lockMemoriaCompartidaJugadores=new LockMemoriaCompartidaJugadores(maxCantidadJugadoresPuntaje);
    lockMemoriaCompartidaJugadores->cleanMemoria();
}

ConexionPubEstad::~ConexionPubEstad() {
    delete(this->lockMemoriaCompartidaResultados);
    lockMemoriaCompartidaResultados=NULL;
    delete(this->lockMemoriaCompartidaJugadores);
    lockMemoriaCompartidaJugadores=NULL;
}

bool ConexionPubEstad::addResultado(TResultadoSerializado &resultadoSerializado) {
    return this->lockMemoriaCompartidaResultados->push(resultadoSerializado);
}

bool ConexionPubEstad::addJugadorPuntaje(TJugadorPuntaje &jugadorPuntaje) {
    return this->lockMemoriaCompartidaJugadores->push(jugadorPuntaje);
}