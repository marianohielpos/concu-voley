//
// Created by Mariano Hielpos on 9/23/17.
//

#include "Marea.h"
#include "Logger.h"
#include "MemoriaCompartidaCanchas.h"
#include "SignalHandler.h"
#include "SIGINT_Handler.h"
#include "time.h"
#include "signal.h"


Marea::Marea(Logger* logger, MemoriaCompartidaCanchas* canchas) {

    this->logger = logger;

    this->canchas = canchas;

}

void Marea::run() {

    this->logger->info("Marea incializada");

    srand(getpid());

    SIGINT_Handler sigint_handler;

    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

    while ( sigint_handler.getGracefulQuit() == 0 ) {
        this->logger->info("Proceso de marea corriendo");

        if (this->mareaSubio()) {
            this->logger->info("Marea subió");
        }
        else if (this->mareaBajo()) {
            this->logger->info("Marea bajó");
        }
        else {
            this->logger->info("Marea se quedó en el mismo nivel");
        }

        sleep ( 1 );
    }

    SignalHandler :: destruir ();
    this->logger->info("Proceso de marea termina");
    return;
}


bool Marea::mareaSubio() {
    return (rand() % 5) == 1 ;
}

bool Marea::mareaBajo() {
    return (rand() % 4) == 1 ;
}