//
// Created by rafael on 25/09/17.
//

#include "MemoriaCompartidaJugadores.h"

MemoriaCompartidaJugadores::MemoriaCompartidaJugadores(unsigned int maxCantidadJugadores)
                                                        throw(std::exception){
    this->cantidadMaxJugadores=maxCantidadJugadores;
    inicializarMemoriaJugadorPuntaje();
    inicializarCantidadJugadores();
}

void MemoriaCompartidaJugadores::cleanMemoria() {
    this->cantidadJugadores.escribir(0,0);
}

bool MemoriaCompartidaJugadores::push(const TJugadorPuntaje &jugadorPuntaje) {
    unsigned int cantidadJugadoresAux;
    this->cantidadJugadores.leer(cantidadJugadoresAux,0);
    if(cantidadJugadoresAux<this->cantidadMaxJugadores){
        this->jugadores.escribir(jugadorPuntaje,cantidadJugadoresAux);
        cantidadJugadoresAux++;
        this->cantidadJugadores.escribir(cantidadJugadoresAux,0);
        return true;
    }
    return false;
}

std::list<TJugadorPuntaje>* MemoriaCompartidaJugadores::readAll() {
    std::list<TJugadorPuntaje>* lista=new std::list<TJugadorPuntaje>();
    unsigned int cantidadJugadoresAux;
    this->cantidadJugadores.leer(cantidadJugadoresAux,0);
    for(int offset=0;offset<cantidadJugadoresAux;offset++){
        TJugadorPuntaje jugadorPuntaje;
        this->jugadores.leer(jugadorPuntaje,offset);
        lista->push_back(jugadorPuntaje);
    }
    return lista;
}

void MemoriaCompartidaJugadores::inicializarCantidadJugadores() throw(std::exception){
    if(this->cantidadJugadores.crear(ARCHIVO_MEMORIA_COMPARTIDA_JUGADORES,CARACTER_MEMORIA_CANTIDAD_JUGADORES,1)!=SHM_OK){
        throw(std::exception());
    }else{
        unsigned int cantidadJugadoresLeido;
        this->cantidadJugadores.leer(cantidadJugadoresLeido,0);
        if((cantidadJugadoresLeido>this->cantidadMaxJugadores)||(cantidadJugadoresLeido<0)){
            this->cleanMemoria();
        }
    }
}

void MemoriaCompartidaJugadores::inicializarMemoriaJugadorPuntaje() throw(std::exception){
    if(this->jugadores.crear(ARCHIVO_MEMORIA_COMPARTIDA_JUGADORES,CARACTER_MEMORIA_COMPARTIDA_JUGADORES,cantidadMaxJugadores)!=SHM_OK) {
        throw (std::exception());
    }
}
