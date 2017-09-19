//
// Created by rafael on 17/09/17.
//

#ifndef CONCU_VOLEY_STATISTICSMANAGER_H
#define CONCU_VOLEY_STATISTICSMANAGER_H
#include <FifoLectura.h>
#include "PublicadorWeb.h"
#define ARCHIVO_FIFO_ESTADISTICAS "/tmp/fifoEstadisticas"
class PublicadorDeEstadisticas {

private:

    FifoLectura* fifo=NULL;

    PublicadorWeb publicador;

    static const size_t bufferSize = 100;

public:

    PublicadorDeEstadisticas();

    void update();

    ~PublicadorDeEstadisticas();
};


#endif //CONCU_VOLEY_STATISTICSMANAGER_H
