
#include <iostream>
#include <vector>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <Logger.h>

#include "principal.h"
#include "torneo.h"
#include "../modelo/jugador.h"
#include "../utils/sleep.h"


MainProcess::MainProcess(Opciones opts, Logger* logger) : opts_(opts) {
  this->logger = logger;
}


void MainProcess::run() {

  this->logger->log("Comienzo del programa");


  std::vector<Jugador> v;
  for (int i = 0; i < JUGADORES_PARA_TORNEO; ++i) {
    v.push_back(Jugador(i));
  }

  // Si hay jugadores suficientes, lanzar torneo
  // TODO: si no, esperar a que haya suficientes
  if (v.size() >= JUGADORES_PARA_TORNEO) {
    pid_t pidTorneo = fork();
    if (pidTorneo == 0) {
      Torneo t(v, opts_, this->logger);
      t.run();
      exit(0);
    } else {

      int i = v.size();
      while (i <= opts_.jugadores) {
        milisleep(150);
        this->logger->log("[Principal] enviando señal SIGUSR1 al torneo: " + std::to_string(i));
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
