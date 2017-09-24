//
// Created by rafael on 17/09/17.
//

#include <fcntl.h>
#include "FifoEscritura.h"

FifoEscritura::FifoEscritura(const std::string nombre) : Fifo(nombre){}

FifoEscritura::~FifoEscritura() {}

void FifoEscritura::abrir() {
    fd=open(Fifo::nombre.c_str(),O_RDWR);
}

ssize_t FifoEscritura::escribir(const void *buffer, const ssize_t bufferSize) const {
    return write(fd,buffer,bufferSize);
}