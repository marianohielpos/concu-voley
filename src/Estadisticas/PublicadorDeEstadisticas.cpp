//
// Created by rafael on 17/09/17.
//

#include <iostream>
#include "PublicadorDeEstadisticas.h"
#include "Serializados.h"

PublicadorDeEstadisticas::PublicadorDeEstadisticas(const unsigned maxCantidadResultados) throw(std::exception){
    this->memoriaResultados=new MemoriaCompartidaResultados(maxCantidadResultados);
}

PublicadorDeEstadisticas::~PublicadorDeEstadisticas() {
    delete(memoriaResultados);
    memoriaResultados=NULL;
}

void PublicadorDeEstadisticas::update() {
    std::list<TResultadoSerializado>* lista=this->memoriaResultados->readAll();
    for(std::list<TResultadoSerializado>::iterator it = lista->begin();it!=lista->end();it++){
        publicador.add(*it);
    }
    delete(lista);
    publicador.update();
}