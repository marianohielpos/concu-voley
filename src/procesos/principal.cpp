
#include <iostream>
#include <vector>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "principal.h"
#include "torneo.h"
#include "../modelo/jugador.h"
#include "../utils/sleep.h"


MainProcess::MainProcess(Opciones opts) : opts_(opts) {
}


void MainProcess::run() {


  std::cout << "Proceso main corriendo" << std::endl;

  std::vector<Jugador> v;
  for (int i = 0; i < JUGADORES_PARA_TORNEO; ++i) {
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

      int i = v.size();
      while (i <= opts_.jugadores) {
        milisleep(150);
        std::cout << "[Principal] enviando señal SIGUSR1 al torneo: " << i << std::endl;
        kill(pidTorneo, SIGUSR1);
        i++;
      }
      int status = 0;
      wait(&status);
    }
  }

}

MainProcess::~MainProcess(){
}
