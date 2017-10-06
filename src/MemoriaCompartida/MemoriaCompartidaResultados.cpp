//
// Created by rafael on 23/09/17.
//

#include "MemoriaCompartidaResultados.h"

MemoriaCompartidaResultados::MemoriaCompartidaResultados(unsigned int maxCantidadResultados) throw(std::exception){
    this->cantidadMaxResultados=maxCantidadResultados;
    inicializarMemoriaResultados();
    inicializarCantidadResultados();
}

void MemoriaCompartidaResultados::cleanMemoria() {
    this->cantidadResultados.escribir(0,0);
}

bool MemoriaCompartidaResultados::push(const TResultadoSerializado &resultado) {
    unsigned int cantidadResultadosAux;
    this->cantidadResultados.leer(cantidadResultadosAux,0);
    if(cantidadResultadosAux<this->cantidadMaxResultados){
        this->resultados.escribir(resultado,cantidadResultadosAux);
        cantidadResultadosAux++;
        this->cantidadResultados.escribir(cantidadResultadosAux,0);
        return true;
    }
    return false;
}

std::list<TResultadoSerializado>* MemoriaCompartidaResultados::readAll() {
    std::list<TResultadoSerializado>* lista=new std::list<TResultadoSerializado>();
    unsigned int cantidadResultadosAux;
    this->cantidadResultados.leer(cantidadResultadosAux,0);
    for(int offset=0;offset<cantidadResultadosAux;offset++){
        TResultadoSerializado resultadoSerializado;
        this->resultados.leer(resultadoSerializado,offset);
        lista->push_back(resultadoSerializado);
    }
    return lista;
}

void MemoriaCompartidaResultados::inicializarCantidadResultados() throw(std::exception){
    if(this->cantidadResultados.crear(ARCHIVO_MEMORIA_RESULTADOS,CARACTER_MEMORIA_CANTIDAD_RESULTADOS,1)!=SHM_OK){
        throw(std::exception());
    }else{
        unsigned int cantidadResultadosLeido;
        this->cantidadResultados.leer(cantidadResultadosLeido,0);
        if((cantidadResultadosLeido>this->cantidadMaxResultados)||(cantidadResultadosLeido<0)){
            this->cleanMemoria();
        }
    }
}

void MemoriaCompartidaResultados::inicializarMemoriaResultados() throw(std::exception){
    if(this->resultados.crear(ARCHIVO_MEMORIA_RESULTADOS,CARACTER_MEMORIA_RESULTADOS,cantidadMaxResultados)!=SHM_OK) {
        throw (std::exception());
    }
}