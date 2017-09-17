
#include <iostream>
#include "main_process.h"

MainProcess::MainProcess(Opciones opts) : opts_(opts) {
}


void MainProcess::run() {
  std::cout << "Proceso main corriendo" << std::endl;
}

MainProcess::~MainProcess(){
}
