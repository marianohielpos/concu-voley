//
// Created by rafael on 18/09/17.
//

#include <iostream>
#include "ConexionPubEstad.h"

ConexionPubEstad::ConexionPubEstad(unsigned int maxCantidadResultados, unsigned int maxCantidadJugadoresPuntaje)
                                    throw(std::exception) :
                            lockMemoriaCompartidaResultados(maxCantidadResultados),
                            lockMemoriaCompartidaJugadores(maxCantidadJugadoresPuntaje){
    lockMemoriaCompartidaResultados.cleanMemoria();
    lockMemoriaCompartidaJugadores.cleanMemoria();
}

ConexionPubEstad::~ConexionPubEstad() {}

bool ConexionPubEstad::addResultado(TResultadoSerializado &resultadoSerializado) {
    return this->lockMemoriaCompartidaResultados.push(resultadoSerializado);
}

bool ConexionPubEstad::addJugadorPuntaje(TJugadorPuntaje &jugadorPuntaje) {
    return this->lockMemoriaCompartidaJugadores.push(jugadorPuntaje);
}

void ConexionPubEstad::liberarRecursos() {
    this->lockMemoriaCompartidaResultados.liberarMemoria();
}