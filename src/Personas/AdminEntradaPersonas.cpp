//
// Created by rafael on 14/10/17.
//

#include <Opciones.h>
#include <Logger.h>
#include "AdminEntradaPersonas.h"

AdminEntradaPersonas::AdminEntradaPersonas(Opciones opciones) throw(std::exception):
                                lockMemoriaCompartidaPersonas(opciones.jugadores,opciones.capacidad){
    this->lockMemoriaCompartidaPersonas.cleanMemoria();
}


void AdminEntradaPersonas::update() {
    //vuelvo a llenar la cola si la misma se encuentra vacía
    if(this->cola.empty()){
        llenarCola();
    }
    // intento ingresar una persona
    ingresarPersona();
}

void AdminEntradaPersonas::ingresarPersona() {
    if(!cola.empty()){
        if(this->lockMemoriaCompartidaPersonas.ingresarPersona(this->cola.front())){
            Logger::getInstance()->info("[AdminEntradaPersonas] Entro persona "+std::to_string(cola.front().idPersona));
            this->cola.pop();
        }
    }
}

void AdminEntradaPersonas::llenarCola() {
    this->lockMemoriaCompartidaPersonas.llenarCola(this->cola);
}

void AdminEntradaPersonas::liberarRecursos() {
    this->lockMemoriaCompartidaPersonas.liberarRecursos();
}