
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
  memoriaCompartidaCanchas_(opts_.filas, opts_.columnas),
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


  std::vector<Jugador> v;
  for (int i = 0; i < JUGADORES_PARA_TORNEO; ++i) {
    v.push_back(Jugador(i));
  }

  // Si hay jugadores suficientes, lanzar torneo
  // TODO: si no, esperar a que haya suficientes
  if (v.size() >= JUGADORES_PARA_TORNEO) {
    this->pidTorneo = fork();
    if (this->pidTorneo == 0) {
      Torneo t(v, opts_);
      t.run();
      exit(0);
    } else {

      int i = v.size();
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
  }

  this->matarProcesosHijos();

}

MainProcess::~MainProcess(){
  memoriaCompartidaCanchas_.liberar();
  Logger::getInstance()->info("[Principal] Borrando main process!");
}

void MainProcess::matarProcesosHijos() {

  Logger::getInstance()->info("[Principal] Enviando señales a procesos");

  if (this->pidMarea != 0) kill(this->pidMarea, SIGINT);

  if (this->pidPublicador != 0) kill(this->pidPublicador, SIGINT);

  if (this->pidTorneo != 0) kill(this->pidTorneo, SIGINT);
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

