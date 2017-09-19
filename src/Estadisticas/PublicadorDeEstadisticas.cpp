//
// Created by rafael on 17/09/17.
//

#include <iostream>
#include "PublicadorDeEstadisticas.h"
#include "Serializados.h"

PublicadorDeEstadisticas::PublicadorDeEstadisticas() {
    fifo=new FifoLectura(ARCHIVO_FIFO_ESTADISTICAS);
    fifo->abrir();
}

PublicadorDeEstadisticas::~PublicadorDeEstadisticas() {
    fifo->cerrar();
    delete(fifo);
    fifo=NULL;
}

void PublicadorDeEstadisticas::update() {
    ResultadoSerializado resultados[bufferSize];
    ssize_t bytesLeidos=fifo->leer(resultados,sizeof(resultados));
    if(bytesLeidos>0) {
        unsigned int cantidadResLeidos=bytesLeidos/sizeof(TResultadoSerializado);
        for (int i = 0; i < cantidadResLeidos; i++) {
            publicador.add(resultados[i]);
        }
    }
    publicador.update();
}