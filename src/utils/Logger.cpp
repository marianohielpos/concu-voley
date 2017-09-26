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

Logger::Logger(std::string nombreArchivo, std::string nivel) {

    if(nombreArchivo.empty())
        return;

    this->lock = new LockFile(nombreArchivo);

    this->logLevel = nivel;

}

Logger::~Logger() {
    delete this->lock;
}

std::string Logger::generarMensaje(std::string mensaje, std::string nivel){

    std::stringstream mensajeFormateado;

    mensajeFormateado << nivel;

    if (this->pid) {

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

void Logger::info(std::string mensaje) {

    if( this->levels["info"] < this->levels[this->logLevel] ) return;

    std::string mensajeFormateado = this->generarMensaje(mensaje, "INFO");

    this->imprimirMensaje(mensajeFormateado);

}

void Logger::debug(std::string mensaje) {

    if( this->levels["debug"] < this->levels[this->logLevel] ) return;

    std::string mensajeFormateado = this->generarMensaje(mensaje, "DEBUG");

    this->imprimirMensaje(mensajeFormateado);

}

void Logger::warning(std::string mensaje) {

    if( this->levels["warning"] < this->levels[this->logLevel] ) return;

    std::string mensajeFormateado = this->generarMensaje(mensaje, "WARNING");

    this->imprimirMensaje(mensajeFormateado);

}

void Logger::error(std::string mensaje) {

    if( this->levels["error"] < this->levels[this->logLevel] ) return;

    std::string mensajeFormateado = this->generarMensaje(mensaje, "ERROR");

    this->imprimirMensaje(mensajeFormateado);

}


void Logger::imprimirMensaje(std::string mensaje) {
    if( this->lock == NULL)
        return this->escribirAConsola(mensaje);

    return this->escribirAArchivo(mensaje);
}