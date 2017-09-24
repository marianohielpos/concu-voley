//
// Created by rafael on 18/09/17.
//

#include <iostream>
#include "ConexionPubEstad.h"
#include "PublicadorDeEstadisticas.h"

ConexionPubEstad::ConexionPubEstad(unsigned int maxCantidadResultados) throw(std::exception){
    memoria=new MemoriaCompartidaResultados(maxCantidadResultados);
  //  this->memoria->cleanMemoria();
}

ConexionPubEstad::~ConexionPubEstad() {
    delete(this->memoria);
    memoria=NULL;
}

bool ConexionPubEstad::add(TResultadoSerializado &resultadoSerializado) {
    return this->memoria->push(resultadoSerializado);
}

