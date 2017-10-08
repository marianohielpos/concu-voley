//
// Created by Mariano Hielpos on 9/23/17.
//

#include "Marea.h"
#include "Logger.h"
#include "MemoriaCompartidaCanchas.h"
#include "SignalHandler.h"
#include "SIGINT_Handler.h"
#include "sleep.h"
#include "signal.h"
#include <list>
#include <sstream>


Marea::Marea(Logger* logger, Opciones opciones)
    : logger(logger), opciones(opciones), lockCanchas(opciones) {
}

void Marea::generarMensajeDeLog(std::string mensaje) {
    std::string nivel = std::to_string(this->nivel);
    std::stringstream mensajeFormateado;
    mensajeFormateado << mensaje;
    mensajeFormateado << " Nivel: ";
    mensajeFormateado << nivel.c_str();

    this->logger->info(mensajeFormateado.str());
}

void Marea::run() {

    this->logger->info("Marea incializada");

    srand(getpid());

    SIGINT_Handler sigint_handler;

    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

    while ( sigint_handler.getGracefulQuit() == 0 ) {

        this->generarMensajeDeLog("Proceso de marea corriendo");

        if (this->mareaSubio()) {
            this->generarMensajeDeLog("Marea subió");
            std::list<pid_t> procesosAfectados = this->lockCanchas.inundarFilasDeCanchas(this->nivel - 1);

            std::stringstream mensajeProcesosAfectados;

            mensajeProcesosAfectados << "Procesos afectados:";

            for(std::list<pid_t>::iterator it=procesosAfectados.begin();it!=procesosAfectados.end();++it){
                mensajeProcesosAfectados << " " << std::to_string(*it);
            }

            this->logger->info(mensajeProcesosAfectados.str());

        }
        else if (this->mareaBajo()) {
            this->generarMensajeDeLog("Marea bajó");
            this->lockCanchas.desinundarFilasDeCanchas(this->nivel);
        }
        else {
            this->generarMensajeDeLog("Marea se quedó en el mismo nivel");
        }

        milisleep ( this->opciones.sleepMarea );
    }

    SignalHandler :: destruir ();
    lockCanchas.liberar();
    this->logger->info("Proceso de marea termina");
    return;
}


bool Marea::mareaSubio() {

    bool subio = (rand() % 5) == 1 && this->nivel < (this->opciones.filas - 1);

    if (subio)
        this->nivel++;

    return subio;
}

bool Marea::mareaBajo() {

    bool bajo = (rand() % 4) == 1 && this->nivel > 0;

    if (bajo)
        this->nivel--;

    return bajo;
}
