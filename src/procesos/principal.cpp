
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <Logger.h>
#include <assert.h>
#include <SignalHandler.h>
#include <SIGINT_Handler.h>
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
{
    if (semaforoEntradaJugadores.getId() == -1){
        Logger::getInstance()->error("[Principal] Error creando semaforo ");
        exit(1);
    }
}


void MainProcess::run() {

  Logger::getInstance()->info("[Principal] Comienzo del programa");

    Terminador terminador(*this);
    SignalHandler :: getInstance()->registrarHandler (SIGINT, &terminador);

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
  }

    this->agregadorDeJugadores = fork();
    if (this->agregadorDeJugadores == 0) {
        SIGINT_Handler sigint_handler;
        SignalHandler :: getInstance()->registrarHandler (SIGINT, &sigint_handler);

        while (sigint_handler.getGracefulQuit() != 1) {
            int resultado = semaforoEntradaJugadores.p();

            if (resultado == -1) {
                perror("[Principal] Posible error: ");
                break;
            }
            int i = 0;


            milisleep(this->opts_.sleepJugadores);
            Logger::getInstance()->info("[Principal] enviando señal SIGUSR1 al torneo: " + std::to_string(i));
            kill(pidTorneo, SIGUSR1);

        }

        exit(0);
    }

    int status;

    wait(&status);

    this->pidTorneo = 0;

    Logger::getInstance()->info("[Principal] Elimiando semaforo");

    int resultado = semaforoEntradaJugadores.eliminar();

    if (resultado == -1 ) perror("Error eliminadno semaforo en principal ");

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

    if (this->agregadorDeJugadores != 0) {
        kill(this->agregadorDeJugadores, SIGINT);
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



