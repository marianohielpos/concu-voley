//
// Created by rafael on 04/10/17.
//

#include <signal.h>
#include <SignalHandler.h>
#include <SIGINT_Handler.h>
#include "Publicador.h"
#include "../utils/sleep.h"


Publicador::Publicador(Opciones opts, Logger* logger) throw(std::exception) :
  opts_(opts), logger_(logger), publicadorEstadisticas_(opts_.jugadores * opts_.partidos, opts_.jugadores)
                         {
}

void Publicador::run() {
    this->logger_->info("Publicador incializado");

    SIGINT_Handler sigint_handler;
    SignalHandler :: getInstance()->registrarHandler (SIGINT, &sigint_handler);
    milisleep(opts_.sleepPublicador);
    while(sigint_handler.getGracefulQuit() == 0){
        this->logger_->info("Publicador hace update...");
        this->publicadorEstadisticas_.update();
        milisleep(opts_.sleepPublicador);
    }

    SignalHandler::destruir();
    this->logger_->info("Proceso de publicador termina");
    return;
}

Publicador::~Publicador() {
}
