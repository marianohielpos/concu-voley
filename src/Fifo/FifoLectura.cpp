//
// Created by rafael on 17/09/17.
//

#include <iostream>
#include "FifoLectura.h"
FifoLectura::FifoLectura(const std::string nombre) : Fifo(nombre) {}

FifoLectura::~FifoLectura() {}

void FifoLectura::abrir() {
    fd=open(nombre.c_str(),O_RDONLY|O_NONBLOCK);
}

ssize_t FifoLectura::leer(void *buffer, const ssize_t bufferSize) const {
    return read(fd,buffer,bufferSize);
}