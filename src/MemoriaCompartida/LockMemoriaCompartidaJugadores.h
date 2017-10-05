//
// Created by rafael on 25/09/17.
//

#ifndef CONCU_VOLEY_LOCKMEMORIACOMPARTIDAJUGADORES_H
#define CONCU_VOLEY_LOCKMEMORIACOMPARTIDAJUGADORES_H
#define ARCHIVO_LOCK_MEMORIA_COMPARTIDA_JUGADORES "/tmp/lockMemoriaCompartidaJugadores.tmp"
#include <fcntl.h>
#include <iostream>
#include "MemoriaCompartidaJugadores.h"

class LockMemoriaCompartidaJugadores {

private:

    struct flock fl;

    int fd;

    std::string nombre;

    MemoriaCompartidaJugadores* memoriaCompartidaJugadores=NULL;

public:

    LockMemoriaCompartidaJugadores(unsigned int maxCantidadJugadoresPuntaje)
                                    throw(std::exception);

    ~LockMemoriaCompartidaJugadores();

    int tomarLock ();

    int liberarLock ();

    bool push(const TJugadorPuntaje& jugadorPuntaje);

    void cleanMemoria();

    std::list<TJugadorPuntaje>* readAll();

protected:

    void inicializarLock();
};


#endif //CONCU_VOLEY_LOCKMEMORIACOMPARTIDAJUGADORES_H
