//
// Created by rafael on 17/09/17.
//

#ifndef CONCU_VOLEY_STATISTICSMANAGER_H
#define CONCU_VOLEY_STATISTICSMANAGER_H
#include <FifoLectura.h>
#include <MemoriaCompartidaResultados.h>
#include "PublicadorWeb.h"
#include "LockMemoriaCompartidaResultados.h"

class PublicadorDeEstadisticas {

private:

    MemoriaCompartidaResultados* memoriaResultados=NULL;
    LockMemoriaCompartidaResultados* lock=NULL;
    PublicadorWeb publicador;


public:

    PublicadorDeEstadisticas(const unsigned maxCantidadResultados) throw(std::exception);

    void update();

    ~PublicadorDeEstadisticas();
};


#endif //CONCU_VOLEY_STATISTICSMANAGER_H
