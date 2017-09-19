//
// Created by rafael on 18/09/17.
//

#include <iostream>
#include "ConexionPubEstad.h"
#include "PublicadorDeEstadisticas.h"

ConexionPubEstad::ConexionPubEstad() {
    fifo = new FifoEscritura(ARCHIVO_FIFO_ESTADISTICAS);
    fifo->abrir();
}

void ConexionPubEstad::add(TResultadoSerializado &resultadoSerializado) {
    fifo->escribir(&resultadoSerializado,sizeof(TResultadoSerializado));
}

ConexionPubEstad::~ConexionPubEstad() {
    fifo->cerrar();
    delete(fifo);
    fifo=NULL;
}