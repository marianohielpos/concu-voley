//
// Created by Mariano Hielpos on 9/10/17.
//

#include "Logger.h"
#include "../ipc/LockFile.h"
#include <unistd.h>
#include <sys/types.h>

Logger::Logger(std::string nombre) {
    this->lock = new LockFile(nombre);
}

Logger::~Logger() {
    delete this->lock;
}

void Logger::log(std::string texto) {

    this->lock->tomarLock();

    pid_t pid = getpid();

    std::string texto_a_grabar = "PID: ";

    texto_a_grabar += std::to_string(pid);

    texto_a_grabar += " Mensaje: ";

    texto_a_grabar +=  texto;

    texto_a_grabar +=  "\n";

    this->lock->escribir(texto_a_grabar.c_str(), texto_a_grabar.size());

    this->lock->liberarLock();

}
