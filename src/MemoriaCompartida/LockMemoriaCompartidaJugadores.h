//
// Created by rafael on 25/09/17.
//

#ifndef CONCU_VOLEY_LOCKMEMORIACOMPARTIDAJUGADORES_H
#define CONCU_VOLEY_LOCKMEMORIACOMPARTIDAJUGADORES_H
#define ARCHIVO_LOCK_MEMORIA_COMPARTIDA_JUGADORES "/tmp/lockMemoriaCompartidaJugadores.tmp"
#include <fcntl.h>
#include <iostream>
#include "MemoriaCompartidaJugadores.h"

/**
 * Permite acceder a la memoria compartida de jugadores bajo mecanismos de lock.
 */
class LockMemoriaCompartidaJugadores {

private:

    struct flock fl;

    int fd;

    std::string nombre;

    MemoriaCompartidaJugadores* memoriaCompartidaJugadores=NULL;

public:

    /**
     * @throws: exception en caso de no poder acceder a la memoria asociada.
     */
    LockMemoriaCompartidaJugadores(unsigned int maxCantidadJugadoresPuntaje)
                                    throw(std::exception);

    ~LockMemoriaCompartidaJugadores();

    /**
     * Se accede a la memoria bajo mecanismos de lock.
     * @return verdadero en caso de poder insertar el par jugador-puntaje en la memoria
     * correspondiente. Falso en caso contrario.
     */
    bool push(const TJugadorPuntaje& jugadorPuntaje);

    /**
     * Se accede a la memoria bajo mecanismos de lock.
     * Limpia la memoria compartida asociada de contenido.
     */
    void cleanMemoria();

    /**
     * Se accede a la memoria bajo mecanismos de lock.
     * @return una lista con el contenido de la memoria compartida. La destrucción de la
     * misma queda a cargo del usuario.
     */
    std::list<TJugadorPuntaje>* readAll();

    /**
     * libera los recursos de memoria compartida asociados a la instancia.
     */
    void liberarMemoria();

private:

    int tomarLock ();

    int liberarLock ();

    void inicializarLock();
};


#endif //CONCU_VOLEY_LOCKMEMORIACOMPARTIDAJUGADORES_H
