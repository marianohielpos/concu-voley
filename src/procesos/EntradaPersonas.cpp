//
// Created by rafael on 15/10/17.
//

#include <SIGINT_Handler.h>
#include <SignalHandler.h>
#include <sleep.h>
#include <Opciones.h>
#include "EntradaPersonas.h"
#include "Logger.h"

EntradaPersonas::EntradaPersonas(Opciones opts) throw(std::exception) :
        opts_(opts), adminEntradaPersonas(opts){
}

void EntradaPersonas::run() {
    Logger::getInstance()->info("[Entrada Personas] Entrada Personas incializado");
    SIGINT_Handler sigint_handler;
    SignalHandler :: getInstance()->registrarHandler (SIGINT, &sigint_handler);
    while(sigint_handler.getGracefulQuit() == 0){
        Logger::getInstance()->info("[Entrada Personas] Entrada Personas hace update.");
        this->adminEntradaPersonas.update();
        milisleep(opts_.sleepJugadores);
    }
    SignalHandler::destruir();
    Logger::getInstance()->info("[Entrada Personas] Proceso de Entrada Personas termina");
    this->adminEntradaPersonas.liberarRecursos();
    return;
}

EntradaPersonas::~EntradaPersonas() {}