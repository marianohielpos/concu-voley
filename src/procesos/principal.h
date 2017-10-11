
#ifndef __MAIN_PROCESS_H__
#define __MAIN_PROCESS_H__


#include <MemoriaCompartidaCanchas.h>
#include <EventHandler.h>
#include "../utils/Opciones.h"
#include "Logger.h"

class MainProcess {

Opciones opts_;
MemoriaCompartidaCanchas memoriaCompartidaCanchas_;

private:
    pid_t pidPublicador;
    pid_t pidMarea;
    pid_t pidTorneo;

    Logger* logger = NULL;

public:
    MainProcess(Opciones opts, Logger* logger);
    ~MainProcess();

    void enviarSeñalDeTerminacion();

    void run();

    void enviarSeñalDeTerminacionPorInterrupcion();
};

class Terminador : public EventHandler {

    MainProcess& m_;

public:

    Terminador(MainProcess& m_);

    virtual int handleSignal (int signum);

    ~Terminador();
};



#endif // MAIN_PROCESS_H

