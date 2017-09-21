//
// Created by Mariano Hielpos on 9/10/17.
//

#include "Logger.h"
#include "../ipc/LockFile.h"
#include <unistd.h>
#include <sys/types.h>

Logger::Logger(std::string nombre) {

    if(nombre.size() != 0)
        this->lock = new LockFile(nombre);

    this->lock = NULL;
}

Logger::~Logger() {
    delete this->lock;
}


std::string Logger::generarMensaje(std::string mensaje){

    std::stringstream mensajeFormateado;

    if (this->timestamp) {

        mensajeFormateado << " PID: ";

        mensajeFormateado << std::to_string(getpid());

    }

    if (this->timestamp)
    {
        mensajeFormateado << " TS: ";

        mensajeFormateado << std::to_string(1);
    }

    mensajeFormateado << " Mensaje: ";

    mensajeFormateado <<  mensaje;

    mensajeFormateado <<  "\n";

    return mensajeFormateado.str();
}

void Logger::escribirAArcivo(std::string mensaje) {
    this->lock->tomarLock();

    this->lock->escribir(mensaje.c_str(), mensaje.size());

    this->lock->liberarLock();
}

void Logger::escribirASalidaEstandard(std::string mensaje) {
    std::cout << mensaje.c_str;
}

void Logger::log(std::string mensaje) {

    std::string mensajeFormateado = this->generarMensaje(mensaje);

    if( this->lock != NULL)
        return this->escribirAArcivo(mensajeFormateado);

    return this->escribirASalidaEstandard(mensajeFormateado);

}
