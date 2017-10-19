
#ifndef __MAIN_PROCESS_H__
#define __MAIN_PROCESS_H__


#include <MemoriaCompartidaCanchas.h>
#include <EventHandler.h>
#include <Opciones.h>
#include "../utils/Opciones.h"
#include "Logger.h"
#include "../Semaforo/Semaforo.h"

class MainProcess {

Opciones opts_;

private:
    pid_t pidPublicador;
    pid_t pidMarea;
    pid_t pidTorneo;
    pid_t agregadorDeJugadores;
    Semaforo semaforoEntradaJugadores;

public:
    MainProcess(Opciones opts);
    ~MainProcess();

    void matarProcesosHijos();

    void run();

    void matarProcesosHijosPorInterrupcion();
};

class Terminador : public EventHandler {

    MainProcess& m_;

public:

    Terminador(MainProcess& m_);

    virtual int handleSignal (int signum);

    ~Terminador();
};



#endif // MAIN_PROCESS_H

