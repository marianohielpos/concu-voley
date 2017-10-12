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


Marea::Marea(Opciones opciones)
    :opciones(opciones), lockCanchas(opciones) {
}

void Marea::generarMensajeDeLog(std::string mensaje) {
    std::string nivel = std::to_string(this->nivel);
    std::stringstream mensajeFormateado;
    mensajeFormateado << mensaje;
    mensajeFormateado << " Nivel: ";
    mensajeFormateado << nivel.c_str();

    Logger::getInstance()->info(mensajeFormateado.str());
}

void Marea::run() {

    Logger::getInstance()->info("[Marea] Marea incializada");

    srand(getpid());

    SIGINT_Handler sigint_handler;

    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

    while ( sigint_handler.getGracefulQuit() == 0 ) {

        this->generarMensajeDeLog("[Marea] Proceso de marea corriendo");

        if (this->mareaSubio()) {
            this->generarMensajeDeLog("[Marea] Marea subió");
            std::list<pid_t> procesosAfectados = this->lockCanchas.inundarFilasDeCanchas(this->nivel - 1);

            std::stringstream mensajeProcesosAfectados;

            mensajeProcesosAfectados << "[Marea] Procesos afectados:";

            for(std::list<pid_t>::iterator it=procesosAfectados.begin();it!=procesosAfectados.end();++it){
                mensajeProcesosAfectados << " " << std::to_string(*it);
            }

            Logger::getInstance()->info(mensajeProcesosAfectados.str());

        }
        else if (this->mareaBajo()) {
            this->generarMensajeDeLog("[Marea] Marea bajó");
            this->lockCanchas.desinundarFilasDeCanchas(this->nivel);
        }
        else {
            this->generarMensajeDeLog("[Marea] Marea se quedó en el mismo nivel");
        }

        milisleep ( this->opciones.sleepMarea );
    }

    SignalHandler :: destruir ();
    lockCanchas.liberar();
    Logger::getInstance()->info("[Marea] Proceso de marea termina");
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
