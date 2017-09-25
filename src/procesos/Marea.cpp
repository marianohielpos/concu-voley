//
// Created by Mariano Hielpos on 9/23/17.
//

#include "Marea.h"
#include "Logger.h"
#include "MemoriaCompartidaCanchas.h"
#include "SignalHandler.h"
#include "SIGINT_Handler.h"


Marea::Marea(Logger* logger, MemoriaCompartidaCanchas* canchas) {

    this->logger = logger;

    this->canchas = canchas;

}

void Marea::run() {

    this->logger->info("Marea incializada");

    SIGINT_Handler sigint_handler;

    // se registra el event handler declarado antes
    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

    // mientras no se reciba la senial SIGINT, el proceso realiza su trabajo
    while ( sigint_handler.getGracefulQuit() == 0 ) {
        this->logger("Proceso de marea corriendo");
        sleep ( 2 );
    }

    // se recibio la senial SIGINT, el proceso termina
    SignalHandler :: destruir ();
    this->logger("Proceso de marea termina");
    return 0;
}