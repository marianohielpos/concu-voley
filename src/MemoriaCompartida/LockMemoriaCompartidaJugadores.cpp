//
// Created by rafael on 25/09/17.
//

#include "LockMemoriaCompartidaJugadores.h"

LockMemoriaCompartidaJugadores ::LockMemoriaCompartidaJugadores(unsigned int maxCantidadJugadoresPuntaje)
                                                                throw(std::exception) {
    this->nombre=ARCHIVO_LOCK_MEMORIA_COMPARTIDA_JUGADORES;
    this->inicializarLock();
    this->tomarLock();
    try{
        this->memoriaCompartidaJugadores=new MemoriaCompartidaJugadores(maxCantidadJugadoresPuntaje);
    }catch(std::exception e){
        this->liberarLock();
        throw e;
    }
    this->liberarLock();
}

int LockMemoriaCompartidaJugadores :: tomarLock () {
    this->fl.l_type = F_WRLCK;
    return fcntl ( this->fd,F_SETLKW,&(this->fl) );
}

int LockMemoriaCompartidaJugadores :: liberarLock () {
    this->fl.l_type = F_UNLCK;
    return fcntl ( this->fd,F_SETLK,&(this->fl) );
}

LockMemoriaCompartidaJugadores :: ~LockMemoriaCompartidaJugadores () {
    close ( this->fd );
}

void LockMemoriaCompartidaJugadores::inicializarLock() {
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    this->fd = open ( this->nombre.c_str(),O_CREAT | O_WRONLY,0666 );
}

bool LockMemoriaCompartidaJugadores::push(const TJugadorPuntaje &jugadorPuntaje) {
    this->tomarLock();
    bool retorno=this->memoriaCompartidaJugadores->push(jugadorPuntaje);
    this->liberarLock();
    return retorno;
}

std::list<TJugadorPuntaje>* LockMemoriaCompartidaJugadores::readAll() {
    std::list<TJugadorPuntaje>* retorno;
    this->tomarLock();
    retorno=this->memoriaCompartidaJugadores->readAll();
    this->liberarLock();
    return retorno;
}

void LockMemoriaCompartidaJugadores::cleanMemoria() {
    this->tomarLock();
    this->memoriaCompartidaJugadores->cleanMemoria();
    this->liberarLock();
}
