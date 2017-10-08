//
// Created by Mariano Hielpos on 9/23/17.
//

#ifndef CONCU_VOLEY_MAREA_H
#define CONCU_VOLEY_MAREA_H
#include "Logger.h"
#include "MemoriaCompartidaCanchas.h"
#include "Opciones.h"

class Marea {

private:
    Logger* logger = NULL;

    MemoriaCompartidaCanchas* canchas = NULL;

    bool gracefulQuit = false;

    bool mareaSubio();

    bool mareaBajo();

    pid_t* leerProcesosEnCancha();

    void enviarSIGINTAproceso(pid_t pid);

    Opciones opciones;

    int nivel = 0;

    void generarMensajeDeLog(std::string mensaje);

public:
    Marea(Logger* logger, MemoriaCompartidaCanchas* canchas, Opciones opciones);

    void handleSignal(int signum);

    void run();
};


#endif //CONCU_VOLEY_MAREA_H
