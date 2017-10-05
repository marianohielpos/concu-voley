
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
#include "Publicador.h"


MainProcess::MainProcess(Opciones opts, Logger* logger) : opts_(opts) {
  this->logger = logger;
}


void MainProcess::run() {

  this->logger->info("Comienzo del programa");

  pid_t pid_publicador = fork();
  if (pid_publicador == 0) {
    Publicador publicador = Publicador(this->opts_, this->logger);
    publicador.run();
    exit(0);
  }


  pid_t pid_marea = fork();
  if (pid_marea == 0) {
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

  kill(pid_marea, SIGINT);
  kill(pid_publicador, SIGINT);

}

MainProcess::~MainProcess(){
}
