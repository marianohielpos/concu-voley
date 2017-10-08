
#ifndef __MAIN_PROCESS_H__
#define __MAIN_PROCESS_H__


#include <MemoriaCompartidaCanchas.h>
#include "../utils/Opciones.h"
#include "Logger.h"

class MainProcess {

Opciones opts_;

protected:
    Logger* logger = NULL;

public:
    MainProcess(Opciones opts, Logger* logger, MemoriaCompartidaCanchas* memoriaCompartidaCanchas);
    ~MainProcess();

    void run();

    MemoriaCompartidaCanchas *memoriaCompartidaCanchas;
};


#endif // MAIN_PROCESS_H

