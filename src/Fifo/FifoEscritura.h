//
// Created by rafael on 17/09/17.
//

#ifndef CONCU_VOLEY_FIFOESCRITURA_H
#define CONCU_VOLEY_FIFOESCRITURA_H


#include "Fifo.h"

class FifoEscritura : public Fifo{

public:
    FifoEscritura(const std::string nombre);

    ~FifoEscritura();

    void abrir();

    ssize_t escribir(const void* buffer, const ssize_t bufferSize) const;
};


#endif //CONCU_VOLEY_FIFOESCRITURA_H
