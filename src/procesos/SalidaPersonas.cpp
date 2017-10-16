//
// Created by rafael on 15/10/17.
//

#include "SalidaPersonas.h"
#include <SIGINT_Handler.h>
#include <SignalHandler.h>
#include <sleep.h>
#include "Logger.h"

SalidaPersonas::SalidaPersonas(Opciones opts) throw(std::exception) :
        opts_(opts), adminSalidaPersonas(opts){
}

void SalidaPersonas::run() {
    Logger::getInstance()->info("[Salida Personas] Salida Personas incializado");

    SIGINT_Handler sigint_handler;
    SignalHandler :: getInstance()->registrarHandler (SIGINT, &sigint_handler);

    while(sigint_handler.getGracefulQuit() == 0){
        milisleep(opts_.sleepJugadores);
        Logger::getInstance()->info("[Salida Personas] Salidada Personas hace update...");
        this->adminSalidaPersonas.update();
    }

    SignalHandler::destruir();
    Logger::getInstance()->info("[Salida Personas] Proceso de Salida Personas termina");
    this->adminSalidaPersonas.liberarRecursos();
    return;
}

SalidaPersonas::~SalidaPersonas() {}
