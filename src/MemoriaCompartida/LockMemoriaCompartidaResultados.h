//
// Created by rafael on 24/09/17.
//

#ifndef CONCU_VOLEY_LOCKMEMORIACOMPARTIDARESULTADOS_H
#define CONCU_VOLEY_LOCKMEMORIACOMPARTIDARESULTADOS_H
#define ARCHIVO_MEMORIA_COMPARTIDA_RESULTADOS "/tmp/memoriaCompartidaResultados.tmp"
#include <fcntl.h>
#include <iostream>
#include "MemoriaCompartidaResultados.h"

class LockMemoriaCompartidaResultados{

private:

    struct flock fl;

    int fd;

    std::string nombre;

    MemoriaCompartidaResultados* memoriaCompartidaResultados=NULL;

public:

    LockMemoriaCompartidaResultados(MemoriaCompartidaResultados* memoriaCompartidaResultados) throw(std::exception);

    ~LockMemoriaCompartidaResultados();

    int tomarLock ();

    int liberarLock ();

    bool push(const TResultadoSerializado& resultado);

    void cleanMemoria();

    std::list<TResultadoSerializado>* readAll();

protected:

    void inicializarLock();
};

#endif //CONCU_VOLEY_LOCKMEMORIACOMPARTIDARESULTADOS_H
