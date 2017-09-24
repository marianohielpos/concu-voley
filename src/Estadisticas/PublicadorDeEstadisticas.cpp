//
// Created by rafael on 17/09/17.
//

#include <iostream>
#include "PublicadorDeEstadisticas.h"
#include "Serializados.h"

PublicadorDeEstadisticas::PublicadorDeEstadisticas(const unsigned maxCantidadResultados) throw(std::exception){
    this->memoriaResultados=new MemoriaCompartidaResultados(maxCantidadResultados);
    this->lock=new LockMemoriaCompartidaResultados(memoriaResultados);
}

PublicadorDeEstadisticas::~PublicadorDeEstadisticas() {
    delete(memoriaResultados);
    delete(lock);
    memoriaResultados=NULL;
    lock=NULL;
}

void PublicadorDeEstadisticas::update() {
    std::list<TResultadoSerializado>* lista=this->lock->readAll();
    for(std::list<TResultadoSerializado>::iterator it = lista->begin();it!=lista->end();it++){
        publicador.add(*it);
    }
    delete(lista);
    publicador.update();
}