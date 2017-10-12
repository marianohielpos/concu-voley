//
// Created by Mariano Hielpos on 9/23/17.
//

#ifndef CONCU_VOLEY_MAREA_H
#define CONCU_VOLEY_MAREA_H
#include "Logger.h"
#include "LockMemoriaCompartidaCanchas.h"
#include "Opciones.h"

class Marea {

private:
    LockMemoriaCompartidaCanchas lockCanchas;

    bool gracefulQuit = false;

    bool mareaSubio();

    bool mareaBajo();

    Opciones opciones;

    int nivel = 0;

    void generarMensajeDeLog(std::string mensaje);

public:
    Marea(Opciones opciones);

    void handleSignal(int signum);

    void run();
};


#endif //CONCU_VOLEY_MAREA_H
