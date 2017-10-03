//
// Created by rafael on 24/09/17.
//

#ifndef CONCU_VOLEY_LOCKMEMORIACOMPARTIDACANCHAS_H
#define CONCU_VOLEY_LOCKMEMORIACOMPARTIDACANCHAS_H
#define ARCHIVO_MEMORIA_COMPARTIDA_CANCHAS "/tmp/memoriaCompartidaCanchas.tmp"
#include <fcntl.h>
#include <iostream>
#include "MemoriaCompartidaCanchas.h"

class LockMemoriaCompartidaCanchas {

private:

    struct flock fl;

    int fd;

    std::string nombre;

    MemoriaCompartidaCanchas* memoriaCompartidaCanchas=NULL;

public:

    LockMemoriaCompartidaCanchas(MemoriaCompartidaCanchas* memoriaCompartidaCanchas) throw(std::exception);

    ~LockMemoriaCompartidaCanchas();

    int tomarLock ();

    int liberarLock ();

    /**
     *
     * @throws: lanza una excepción en caso de no poder acceder a la memoria de la cancha dada.
     */
    void leer(TCanchaSerializada& cancha,const unsigned int fila,const unsigned int columna) throw(std::exception);

    /**
     *
     * @throws: lanza una excepción en caso de no poder acceder a la memoria de la cancha dada.
     */
    void escribir(const TCanchaSerializada& cancha) throw(std::exception);

protected:

    void inicializarLock();
};


#endif //CONCU_VOLEY_LOCKMEMORIACOMPARTIDACANCHAS_H
