//
// Created by rafael on 18/09/17.
//

#ifndef CONCU_VOLEY_CONEXIONPUBESTAD_H
#define CONCU_VOLEY_CONEXIONPUBESTAD_H
#include <Serializados.h>
#include "MemoriaCompartidaResultados.h"
#include "MemoriaCompartidaJugadores.h"
#include "LockMemoriaCompartidaResultados.h"
#include "LockMemoriaCompartidaJugadores.h"

class ConexionPubEstad {

private:

    LockMemoriaCompartidaResultados* lockMemoriaCompartidaResultados=NULL;

    LockMemoriaCompartidaJugadores* lockMemoriaCompartidaJugadores=NULL;

public:

    ConexionPubEstad(unsigned int maxCantidadResultados,
                     unsigned int maxCantidadJugadoresPuntaje)
                    throw(std::exception);

    ~ConexionPubEstad();

    bool addResultado(TResultadoSerializado &resultadoSerializado);

    bool addJugadorPuntaje(TJugadorPuntaje &jugadorPuntaje);

};


#endif //CONCU_VOLEY_CONEXIONPUBESTAD_H
