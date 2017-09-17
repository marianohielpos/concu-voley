
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

#include "principal.h"
#include "torneo.h"
#include "../modelo/jugador.h"


MainProcess::MainProcess(Opciones opts) : opts_(opts) {
}


void MainProcess::run() {
  std::cout << "Proceso main corriendo" << std::endl;

  std::vector<Jugador> v;
  for (int i = 0; i < opts_.jugadores; ++i) {
    v.push_back(Jugador(i));
  }

  // Si hay jugadores suficientes, lanzar torneo
  // TODO: si no, esperar a que haya suficientes
  if (v.size() >= JUGADORES_PARA_TORNEO) {
    pid_t pidTorneo = fork();
    if (pidTorneo == 0) {
      Torneo t(v, opts_);
      t.run();
      exit(0);
    } else {
      int status = 0;
      wait(&status);
    }
  }

}

MainProcess::~MainProcess(){
}
