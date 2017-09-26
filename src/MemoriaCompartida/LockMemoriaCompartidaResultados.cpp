//
// Created by rafael on 24/09/17.
//

#include "LockMemoriaCompartidaResultados.h"
#include <unistd.h>

LockMemoriaCompartidaResultados ::LockMemoriaCompartidaResultados(MemoriaCompartidaResultados* memoriaCompartidaResultados) throw(std::exception) {
    this->nombre=ARCHIVO_LOCK_MEMORIA_COMPARTIDA_RESULTADOS;
    if(memoriaCompartidaResultados == NULL){
        throw(std::exception());
    }
    this->memoriaCompartidaResultados=memoriaCompartidaResultados;
    this->inicializarLock();
}

int LockMemoriaCompartidaResultados :: tomarLock () {
    this->fl.l_type = F_WRLCK;
    return fcntl ( this->fd,F_SETLKW,&(this->fl) );
}

int LockMemoriaCompartidaResultados :: liberarLock () {
    this->fl.l_type = F_UNLCK;
    return fcntl ( this->fd,F_SETLK,&(this->fl) );
}

LockMemoriaCompartidaResultados :: ~LockMemoriaCompartidaResultados () {
    close ( this->fd );
}

void LockMemoriaCompartidaResultados::inicializarLock() {
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    this->fd = open ( this->nombre.c_str(),O_CREAT | O_WRONLY,0666 );
}

bool LockMemoriaCompartidaResultados::push(const TResultadoSerializado &resultado) {
    this->tomarLock();
    bool retorno=this->memoriaCompartidaResultados->push(resultado);
    this->liberarLock();
    return retorno;
}

std::list<TResultadoSerializado>* LockMemoriaCompartidaResultados::readAll() {
    std::list<TResultadoSerializado>* retorno;
    this->tomarLock();
    retorno=this->memoriaCompartidaResultados->readAll();
    this->liberarLock();
    return retorno;
}

void LockMemoriaCompartidaResultados::cleanMemoria() {
    this->tomarLock();
    this->memoriaCompartidaResultados->cleanMemoria();
    this->liberarLock();
}
