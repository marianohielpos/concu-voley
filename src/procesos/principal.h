
#ifndef __MAIN_PROCESS_H__
#define __MAIN_PROCESS_H__


#include "../utils/Opciones.h"
#include "Logger.h"

class MainProcess {

Opciones opts_;

protected:
    Logger* logger = NULL;

public:
    MainProcess(Opciones opts, Logger* logger);
    ~MainProcess();

    void run();
};


#endif // MAIN_PROCESS_H

