
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
#include "EntradaPersonas.h"
#include "SalidaPersonas.h"

MainProcess::MainProcess(Opciones opts): opts_(opts), pidMarea(0), pidPublicador(0),
                        pidTorneo(0),pidEntradaPersonas(0), pidSalidaPersonas(0){
}

void MainProcess::run() {
  Logger::getInstance()->info("[Principal] Comienzo del programa");
  Terminador sigint_handler(*this);
  SignalHandler :: getInstance()->registrarHandler (SIGINT, &sigint_handler);
  //creo un proceso para entrada personas
  this->pidEntradaPersonas=fork();
  if(this->pidEntradaPersonas == 0)
    this->iniciarEntradaPersonas();
  //creo un proceso para salida personas
  this->pidSalidaPersonas=fork();
  if(this->pidSalidaPersonas == 0)
    this->iniciarSalidaPersonas();
  // creo un proceso para publicador
  this->pidPublicador = fork();
  if (this->pidPublicador == 0)
    this->iniciarPublicador();
  // creo un proceso para la marea
  this->pidMarea = fork();
  if (this->pidMarea == 0)
    this->iniciarMarea();
  // inicio el torneo con el proceso actual
  this->iniciarTorneo();
}

void MainProcess::iniciarEntradaPersonas(){
  Logger::getInstance()->info("[Principal] Iniciar EntradaPersonas.");
  EntradaPersonas entradaPersonas(this->opts_);
  entradaPersonas.run();
  exit(0);
}

void MainProcess::iniciarSalidaPersonas(){
  SalidaPersonas salidaPersonas(this->opts_);
  salidaPersonas.run();
  exit(0);
}

void MainProcess::iniciarPublicador() {
  Publicador publicador(this->opts_);
  publicador.run();
  exit(0);
}

void MainProcess::iniciarMarea() {
  Marea marea(this->opts_);
  marea.run();
  exit(0);
}

void MainProcess::iniciarTorneo() {
  this->pidTorneo = fork();
  if (this->pidTorneo == 0) {
    Torneo t(opts_);
    t.run();
    exit(0);
  } else {
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

  if (this->pidEntradaPersonas != 0) {
    kill(this->pidEntradaPersonas, SIGINT);
    procesosMatados++;
  }

  if (this->pidSalidaPersonas != 0) {
    kill(this->pidSalidaPersonas, SIGINT);
    procesosMatados++;
  }

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

