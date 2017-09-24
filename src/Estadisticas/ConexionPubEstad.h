//
// Created by rafael on 18/09/17.
//

#ifndef CONCU_VOLEY_CONEXIONPUBESTAD_H
#define CONCU_VOLEY_CONEXIONPUBESTAD_H
#include <Serializados.h>
#include "MemoriaCompartidaResultados.h"
#include "LockMemoriaCompartidaResultados.h"

class ConexionPubEstad {

private:

    LockMemoriaCompartidaResultados* lock=NULL;
    MemoriaCompartidaResultados* memoria=NULL;

public:

    ConexionPubEstad(unsigned int maxCantidadResultados) throw(std::exception);

    ~ConexionPubEstad();

    bool add(TResultadoSerializado &resultadoSerializado);

};


#endif //CONCU_VOLEY_CONEXIONPUBESTAD_H
