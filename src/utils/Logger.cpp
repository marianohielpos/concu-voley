//
// Created by Mariano Hielpos on 9/10/17.
//

#include "Logger.h"
#include "../ipc/LockFile.h"
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <iostream>
#include <sstream>

Logger::Logger(std::string nombre) {

    if(nombre.empty())
        return;

    this->lock = new LockFile(nombre);

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

        mensajeFormateado << std::to_string(time(nullptr));
    }

    mensajeFormateado << " Mensaje: ";

    mensajeFormateado <<  mensaje;

    mensajeFormateado <<  std::endl;

    return mensajeFormateado.str();
}

void Logger::escribirAArchivo(std::string mensaje) {
    this->lock->tomarLock();

    this->lock->escribir(mensaje.c_str(), mensaje.size());

    this->lock->liberarLock();
}

void Logger::escribirAConsola(std::string mensaje) {
    std::cout << mensaje;
}

void Logger::log(std::string mensaje) {

    std::string mensajeFormateado = this->generarMensaje(mensaje);

    if( this->lock == NULL)
        return this->escribirAConsola(mensajeFormateado);

    return this->escribirAArchivo(mensajeFormateado);
}
