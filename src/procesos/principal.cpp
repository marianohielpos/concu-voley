
#include <iostream>
#include <vector>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <Logger.h>
#include <Opciones.h>

#include "principal.h"
#include "torneo.h"
#include "../modelo/jugador.h"
#include "../utils/sleep.h"
#include "Marea.h"


MainProcess::MainProcess(Opciones opts, Logger* logger) : opts_(opts) {
  this->logger = logger;
}


void MainProcess::run() {

  this->logger->info("Comienzo del programa");


  pid_t marea = fork();
  if (marea == 0) {
    Marea marea = Marea(this->logger, nullptr, &this->opts_);
    marea.run();
    exit(0);
  }


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
        milisleep(this->opts_.sleepJugadores);
        this->logger->info("[Principal] enviando señal SIGUSR1 al torneo: " + std::to_string(i));
        kill(pidTorneo, SIGUSR1);
        i++;
      }
      int status = 0;
      wait(&status);
    }
  }

  kill(marea, SIGINT);

}

MainProcess::~MainProcess(){
}
