//
// Created by rafael on 04/10/17.
//

#include <signal.h>
#include <SignalHandler.h>
#include <SIGINT_Handler.h>
#include "Publicador.h"
#include "../utils/sleep.h"


Publicador::Publicador(Opciones opts) throw(std::exception) :
  opts_(opts), publicadorEstadisticas_(opts)
                         {
}

void Publicador::run() {
    Logger::getInstance()->info("[Publicador] Publicador incializado");

    SIGINT_Handler sigint_handler;
    SignalHandler :: getInstance()->registrarHandler (SIGINT, &sigint_handler);

    while(sigint_handler.getGracefulQuit() == 0){
        milisleep(opts_.sleepPublicador);
        Logger::getInstance()->info("[Publicador] Publicador hace update...");
        this->publicadorEstadisticas_.update();
    }

    SignalHandler::destruir();
    Logger::getInstance()->info("[Publicador] Proceso de publicador termina");
    this->publicadorEstadisticas_.liberarRecursos();
    return;
}

Publicador::~Publicador() {
}
