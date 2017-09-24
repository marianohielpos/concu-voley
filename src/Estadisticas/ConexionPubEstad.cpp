//
// Created by rafael on 18/09/17.
//

#include <iostream>
#include "ConexionPubEstad.h"
#include "PublicadorDeEstadisticas.h"

ConexionPubEstad::ConexionPubEstad(unsigned int maxCantidadResultados) throw(std::exception){
    memoria=new MemoriaCompartidaResultados(maxCantidadResultados);
    lock=new LockMemoriaCompartidaResultados(memoria);
    lock->cleanMemoria();
}

ConexionPubEstad::~ConexionPubEstad() {
    delete(this->memoria);
    delete(this->lock);
    memoria=NULL;
    lock=NULL;
}

bool ConexionPubEstad::add(TResultadoSerializado &resultadoSerializado) {
    return this->lock->push(resultadoSerializado);
}

