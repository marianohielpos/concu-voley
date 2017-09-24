//
// Created by rafael on 17/09/17.
//

#ifndef CONCU_VOLEY_FIFOLECTURA_H
#define CONCU_VOLEY_FIFOLECTURA_H
#include "Fifo.h"

class FifoLectura : public Fifo {

public:

    FifoLectura(const std::string nombre);

    ~FifoLectura();

    void abrir();

    ssize_t leer(void* buffer, const ssize_t bufferSize) const;
};


#endif //CONCU_VOLEY_FIFOLECTURA_H
