//
// Created by rafael on 15/10/17.
//

#include "AdminSalidaPersonas.h"

AdminSalidaPersonas::AdminSalidaPersonas(Opciones opciones) throw(std::exception):
                lockMemoriaCompartidaPersonas(opciones.jugadores,opciones.capacidad){
}

void AdminSalidaPersonas::update() {
    // intento dar salida a una persona
    retirarPersona();
}


void AdminSalidaPersonas::retirarPersona() {
    this->lockMemoriaCompartidaPersonas.retirarPersona();
}

void AdminSalidaPersonas::liberarRecursos() {
    this->lockMemoriaCompartidaPersonas.liberarRecursos();
}