
#ifndef __MAIN_PROCESS_H__
#define __MAIN_PROCESS_H__


#include "../utils/Opciones.h"

class MainProcess {

Opciones opts_;


public:
  MainProcess(Opciones opts);
  ~MainProcess();

  void run();

};


#endif // MAIN_PROCESS_H

