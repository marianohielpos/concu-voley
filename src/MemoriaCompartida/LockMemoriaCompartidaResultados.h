//
// Created by rafael on 24/09/17.
//

#ifndef CONCU_VOLEY_LOCKMEMORIACOMPARTIDARESULTADOS_H
#define CONCU_VOLEY_LOCKMEMORIACOMPARTIDARESULTADOS_H
#define ARCHIVO_LOCK_MEMORIA_COMPARTIDA_RESULTADOS "/tmp/lockMemoriaCompartidaResultados.tmp"
#include <fcntl.h>
#include <iostream>
#include "MemoriaCompartidaResultados.h"

/**
 * Una instancia de esta clase permite accceder al contenido de la memoria compartida dada
 * bajo mecanismos de lock.
 */
class LockMemoriaCompartidaResultados{

private:

    struct flock fl;

    int fd;

    std::string nombre;

    MemoriaCompartidaResultados* memoriaCompartidaResultados=NULL;

public:

    /**
     * @throws: exception en caso de no poder crear la instancia debido a problemas al
     * reservar el recurso memoria.
     */
    LockMemoriaCompartidaResultados(unsigned int maxCantidadResultados) throw(std::exception);

    ~LockMemoriaCompartidaResultados();

    /**
     *  Se actualiza el contenido de la memoria compartida de acuerdo al parámetro accediendo
     *  bajo mecanismos de lock.
     *
     * @return verdad si se puede actualizar la memoria de acuerdo al parámetro, falso
     * en caso contrario.
     */
    bool push(const TResultadoSerializado& resultado);

    /**
     * Se limpiar el contenido de la memoria asociada accediendo bajo mecanismo de lock.
     */
    void cleanMemoria();

    /**
     * Se lee el contenido de la memoria compartida bajo mecanismo de lock.
     *
     * @return Una lista con el contenido de la memoria compartida accediendo bajo
     * mecanismos de lock.
     */
    std::list<TResultadoSerializado>* readAll();

    /**
     * libera los recursos de memoria compartida asociados a la instancia.
     */
    void liberarMemoria();

private:

    int tomarLock ();

    int liberarLock ();

    void inicializarLock();
};

#endif //CONCU_VOLEY_LOCKMEMORIACOMPARTIDARESULTADOS_H
