//
// Created by rafael on 17/09/17.
//

#ifndef CONCU_VOLEY_PIPE_H
#define CONCU_VOLEY_PIPE_H
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
class Fifo {

public:
    Fifo(const std::string nombre);

    virtual ~Fifo();

    virtual void abrir() = 0;

    void cerrar();

    void eliminar() const;

protected:

    std::string nombre;

    int fd;

};


#endif //CONCU_VOLEY_PIPE_H
