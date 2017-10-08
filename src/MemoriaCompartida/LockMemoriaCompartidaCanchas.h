//
// Created by rafael on 24/09/17.
//

#ifndef CONCU_VOLEY_LOCKMEMORIACOMPARTIDACANCHAS_H
#define CONCU_VOLEY_LOCKMEMORIACOMPARTIDACANCHAS_H
#define ARCHIVO_MEMORIA_COMPARTIDA_CANCHAS "/tmp/memoriaCompartidaCanchas.tmp"
#include <fcntl.h>
#include <iostream>
#include "MemoriaCompartidaCanchas.h"
#include "../utils/Opciones.h"

/**
 * Permite acceder a la memoria compartida de canchas bajo mecanismos de lock.
 */
class LockMemoriaCompartidaCanchas {

private:

    struct flock fl;

    int fd;

    std::string nombre;

    MemoriaCompartidaCanchas memoriaCompartidaCanchas;

public:
    /**
     *
     * @throws exception en caso de no poder acceder la memoria compartida dada.
     */
    LockMemoriaCompartidaCanchas(Opciones opts_) throw(std::exception);

    ~LockMemoriaCompartidaCanchas();


    /**
     * Accede a la memoria bajo mecanismo de lock.
     * @throws: lanza una excepción en caso de no poder acceder a la memoria de la cancha dada.
     */
    void leer(TCanchaSerializada& cancha,const unsigned int fila,const unsigned int columna) throw(std::exception);

    /**
     * Accede a la memoria bajo mecanismo de lock.
     * @throws: lanza una excepción en caso de no poder acceder a la memoria de la cancha dada.
     */
    void escribir(const TCanchaSerializada& cancha) throw(std::exception);

    void liberar();

    void inundarFilasDeCanchas(int fila);

    void desinundarFilasDeCanchas(int fila);


private:

    int tomarLock ();

    int liberarLock ();

    void inundarDesinundar(int fila, bool inundar);

    void inicializarLock();
};


#endif //CONCU_VOLEY_LOCKMEMORIACOMPARTIDACANCHAS_H
