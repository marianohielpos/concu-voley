//
// Created by rafael on 04/10/17.
//

#include <signal.h>
#include <SignalHandler.h>
#include <SIGINT_Handler.h>
#include "Publicador.h"

Publicador::Publicador(const unsigned maxCantidadResultados, const unsigned maxCantidadJugadores)
                        throw(std::exception) {
    this->publicador=new PublicadorDeEstadisticas(maxCantidadResultados,maxCantidadJugadores);
}

void Publicador::run() {
    SIGINT_Handler sigint_handler;
    SignalHandler :: getInstance()->registrarHandler (SIGQUIT, &sigint_handler);
    while(sigint_handler.getGracefulQuit() == 0){
        this->publicador->update();
    }
    SignalHandler::destruir();
    return;
}

Publicador::~Publicador() {
    delete(this->publicador);
    this->publicador=NULL;
}