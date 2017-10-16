//
// Created by rafael on 14/10/17.
//

#include "MemoriaCompartidaPersonas.h"

MemoriaCompartidaPersonas::MemoriaCompartidaPersonas(unsigned int cantidadPersonas,unsigned int capacidadPredio)
                                                    throw(std::exception){
    this->cantidadPersonas=cantidadPersonas;
    this->capacidadPredio=capacidadPredio;
    inicializarMemoria();
}

void MemoriaCompartidaPersonas::escribir(const TPersona &persona) throw(std::exception){
    this->personas.escribir(persona, persona.idPersona);
}

std::list<TPersona>* MemoriaCompartidaPersonas::readAll() {
    std::list<TPersona>* lista=new std::list<TPersona>();
    for(int offset=0;offset<cantidadPersonas;offset++){
        TPersona persona;
        this->personas.leer(persona,offset);
        lista->push_back(persona);
    }
    return lista;
}

std::list<TPersona>* MemoriaCompartidaPersonas::readAllFueraDelPredio() {
    std::list<TPersona>* lista=new std::list<TPersona>();
    for(int offset=0;offset<cantidadPersonas;offset++){
        TPersona persona;
        this->personas.leer(persona,offset);
        if(!persona.enPredio)
            lista->push_back(persona);
    }
    return lista;
}


std::list<TPersona>* MemoriaCompartidaPersonas::readAllDentroDelPredio() {
    std::list<TPersona>* lista=new std::list<TPersona>();
    for(int offset=0;offset<cantidadPersonas;offset++){
        TPersona persona;
        this->personas.leer(persona,offset);
        if(persona.enPredio)
            lista->push_back(persona);
    }
    return lista;
}


std::list<TPersona>* MemoriaCompartidaPersonas::readAllEnPredioJugando() {
    std::list<TPersona>* lista=new std::list<TPersona>();
    for(int offset=0;offset<cantidadPersonas;offset++){
        TPersona persona;
        this->personas.leer(persona,offset);
        if((persona.jugando)&&(persona.enPredio))
            lista->push_back(persona);
    }
    return lista;
}

std::list<TPersona>* MemoriaCompartidaPersonas::readAllEnPredioEsperandoParaJugar() {
    std::list<TPersona>* lista=new std::list<TPersona>();
    for(int offset=0;offset<cantidadPersonas;offset++){
        TPersona persona;
        this->personas.leer(persona,offset);
        if((!persona.jugando)&&(persona.enPredio))
            lista->push_back(persona);
    }
    return lista;
}

std::vector<TPersona>* MemoriaCompartidaPersonas::readAllAsVector() {
    std::vector<Persona>* retorno=new std::vector<TPersona>();
    for(int offset=0;offset<cantidadPersonas;offset++){
        TPersona persona;
        this->personas.leer(persona,offset);
        retorno->push_back(persona);
    }
    return retorno;
}

void MemoriaCompartidaPersonas::inicializarMemoria() throw(std::exception){
    if(this->personas.crear(ARCHIVO_MEMORIA_COMPARTIDA_PERSONAS,CARACTER_MEMORIA_COMPARTIDA_PERSONAS,cantidadPersonas)!=SHM_OK) {
        throw (std::exception());
    }
}

unsigned int MemoriaCompartidaPersonas::cantidadPersonasDentroDelPredio() {
    std::list<TPersona>* lista=this->readAllDentroDelPredio();
    unsigned int retorno=lista->size();
    delete(lista);
    return retorno;
}

bool MemoriaCompartidaPersonas::capacidadPredioAgotada(){
    return (this->capacidadPredio-this->cantidadPersonasDentroDelPredio())<0;
}

void MemoriaCompartidaPersonas::cleanMemoria(){
    for(int offset=0;offset<cantidadPersonas;offset++){
        TPersona persona;
        persona.init(offset,false,false);
        this->escribir(persona);
    }
}

void MemoriaCompartidaPersonas::liberar() {
    this->personas.liberar();
}