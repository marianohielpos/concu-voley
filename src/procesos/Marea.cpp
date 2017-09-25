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

    SIGINT_Handler sigint_handler;

    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

    while ( sigint_handler.getGracefulQuit() == 0 ) {
        this->logger->info("Proceso de marea corriendo");
        sleep ( 2 );
    }

    SignalHandler :: destruir ();
    this->logger->info("Proceso de marea termina");
    return;
}


bool Marea::mareaSubio() {

    time_t seconds = time(NULL);

    if( seconds == -1)
    {
        this->logger->info("Error desconocido");

        perror("Ocurrió un error ");

        exit(1);
    }

    srand(seconds);

    return (random() % 2) == 1 ;
}