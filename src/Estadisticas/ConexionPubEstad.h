//
// Created by rafael on 18/09/17.
//

#ifndef CONCU_VOLEY_CONEXIONPUBESTAD_H
#define CONCU_VOLEY_CONEXIONPUBESTAD_H


#include <FifoEscritura.h>
#include <Serializados.h>

class ConexionPubEstad {

private:

    FifoEscritura* fifo=NULL;

public:
    ConexionPubEstad();

    ~ConexionPubEstad();

    void add(TResultadoSerializado &resultadoSerializado);
};


#endif //CONCU_VOLEY_CONEXIONPUBESTAD_H
