
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <Logger.h>
#include <assert.h>
#include <SignalHandler.h>
#include "principal.h"
#include "torneo.h"
#include "../utils/sleep.h"
#include "Marea.h"
#include "Publicador.h"


MainProcess::MainProcess(Opciones opts)
: opts_(opts),
  pidMarea(0),
  pidPublicador(0),
  pidTorneo(0)
{}


void MainProcess::run() {

  Logger::getInstance()->info("[Principal] Comienzo del programa");

  Terminador sigint_handler(*this);
  SignalHandler :: getInstance()->registrarHandler (SIGINT, &sigint_handler);

  this->pidPublicador = fork();
  if (this->pidPublicador == 0) {
    Publicador publicador = Publicador(this->opts_);
    publicador.run();
    exit(0);
  }


  this->pidMarea = fork();
  if (this->pidMarea == 0) {
    Marea marea = Marea(this->opts_);
    marea.run();
    exit(0);
  }



  this->pidTorneo = fork();
  if (this->pidTorneo == 0) {
    Torneo t(opts_);
    t.run();
    exit(0);
  } else {

    int i = 0;

    while (i <= opts_.jugadores) {
      milisleep(this->opts_.sleepJugadores);
      Logger::getInstance()->info("[Principal] enviando señal SIGUSR1 al torneo: " + std::to_string(i));
      kill(pidTorneo, SIGUSR1);
      i++;
    }

    int status = 0;

    wait(&status);

    this->pidTorneo = 0;
  }

  this->matarProcesosHijos();

}

MainProcess::~MainProcess(){
}

void MainProcess::matarProcesosHijos() {

  Logger::getInstance()->info("[Principal] Enviando señales a procesos");

  int procesosMatados = 0;

  if (this->pidMarea != 0) {
    kill(this->pidMarea, SIGINT);
    procesosMatados++;
  }

  if (this->pidPublicador != 0) {
    kill(this->pidPublicador, SIGINT);
    procesosMatados++;
  }

  if (this->pidTorneo != 0) {
    kill(this->pidTorneo, SIGINT);
    procesosMatados++;
  }

  for (int i = 0; i < procesosMatados; ++i) {
    int status = 0;
    wait(&status);
  }

  Logger::getInstance()->info("[Principal] Terminado!");
}

void MainProcess::matarProcesosHijosPorInterrupcion() {

  Logger::getInstance()->info("[Principal] Enviando SIGINT a los procesos hijos por interrupción!");

  this->matarProcesosHijos();

}

Terminador::Terminador(MainProcess &mainProcess): m_(mainProcess){}

Terminador::~Terminador() {}

int Terminador::handleSignal (int signum) {
  assert(signum == SIGINT);
    m_.matarProcesosHijosPorInterrupcion();
  exit(SIGINT);
}

