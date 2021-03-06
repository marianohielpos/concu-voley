
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
#include <errno.h>


MainProcess::MainProcess(Opciones opts)
: opts_(opts),
  pidMarea(0),
  pidPublicador(0),
  pidTorneo(0),
  semaforoEntradaJugadores("CMakeLists.txt", opts_.jugadores)
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

        int i = 0;

        while (sigint_handler.getGracefulQuit() != 1) {
            int resultado = semaforoEntradaJugadores.p();

            if (resultado == -1) {
                continue;
            }
            i++;

            milisleep(this->opts_.sleepJugadores);
            Logger::getInstance()->info("[Enviador de jugadores] enviando señal SIGUSR1 al torneo: " + std::to_string(i));
            kill(pidTorneo, SIGUSR1);

        }
        Logger::getInstance()->info("[Enviador de jugadores] Interrumpido por señal! Terminando.");

        exit(0);
    }

    int status;

    pid_t pid = waitpid(this->pidTorneo, &status, 0);

    if (pid != -1)  {
        this->pidTorneo = 0;
    }

    Logger::getInstance()->info("[Principal] Eliminando semaforo");

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


    if (semaforoEntradaJugadores.getId() != -1 ) {

        int resultado = semaforoEntradaJugadores.eliminar();

        if (resultado == -1) {
            char buffer[256];
            strerror_r(errno, buffer, 256);
            Logger::getInstance()->error(buffer);
        }
    };


    for (int i = 0; i < procesosMatados; ++i) {
      int status = 0;
      wait(&status);
    }

  Logger::getInstance()->info("[Principal] Terminado!");
}

void MainProcess::matarProcesosHijosPorInterrupcion() {

  Logger::getInstance()->info("[Principal] Handle señal SIGIN");

    this->matarProcesosHijos();

}

Terminador::Terminador(MainProcess &mainProcess): m_(mainProcess){}

Terminador::~Terminador() {}

int Terminador::handleSignal (int signum) {
    assert(signum == SIGINT);
    m_.matarProcesosHijosPorInterrupcion();
    exit(SIGINT);
}
