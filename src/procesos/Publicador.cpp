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

    while(sigint_handler.getGracefulQuit() == 0){
        milisleep(opts_.sleepPublicador);
        this->logger_->info("Publicador hace update...");
        this->publicadorEstadisticas_.update();
    }

    SignalHandler::destruir();
    this->logger_->info("Proceso de publicador termina");
    this->publicadorEstadisticas_.liberarRecursos();
    return;
}

Publicador::~Publicador() {
}
