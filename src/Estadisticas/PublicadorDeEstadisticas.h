//
// Created by rafael on 17/09/17.
//

#ifndef CONCU_VOLEY_STATISTICSMANAGER_H
#define CONCU_VOLEY_STATISTICSMANAGER_H
#include <FifoLectura.h>
#include <MemoriaCompartidaResultados.h>
#include "PublicadorWeb.h"
#define ARCHIVO_FIFO_ESTADISTICAS "/tmp/fifoEstadisticas"
class PublicadorDeEstadisticas {

private:

    MemoriaCompartidaResultados* memoriaResultados;

    PublicadorWeb publicador;

public:

    PublicadorDeEstadisticas(const unsigned maxCantidadResultados) throw(std::exception);

    void update();

    ~PublicadorDeEstadisticas();
};


#endif //CONCU_VOLEY_STATISTICSMANAGER_H
