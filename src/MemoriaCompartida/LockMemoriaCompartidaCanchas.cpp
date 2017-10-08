//
// Created by rafael on 24/09/17.
//

#include "LockMemoriaCompartidaCanchas.h"

LockMemoriaCompartidaCanchas::LockMemoriaCompartidaCanchas(Opciones opts_) throw(std::exception)
        : memoriaCompartidaCanchas(opts_.filas, opts_.columnas) {
    this->nombre=ARCHIVO_MEMORIA_COMPARTIDA_CANCHAS;
    this->inicializarLock();

    tomarLock();
    memoriaCompartidaCanchas.inicializar();
    liberarLock();
}


int LockMemoriaCompartidaCanchas :: tomarLock () {
    this->fl.l_type = F_WRLCK;
    return fcntl ( this->fd,F_SETLKW,&(this->fl) );
}

int LockMemoriaCompartidaCanchas :: liberarLock () {
    this->fl.l_type = F_UNLCK;
    return fcntl ( this->fd,F_SETLK,&(this->fl) );
}

LockMemoriaCompartidaCanchas :: ~LockMemoriaCompartidaCanchas () {
    close ( this->fd );
}

void LockMemoriaCompartidaCanchas :: liberar () {
    memoriaCompartidaCanchas.liberar();
}

void LockMemoriaCompartidaCanchas::inicializarLock() {
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    this->fd = open ( this->nombre.c_str(),O_CREAT | O_WRONLY,0666 );
}

void LockMemoriaCompartidaCanchas::leer(TCanchaSerializada &cancha, const unsigned int fila,
                                        const unsigned int columna) throw(std::exception){
    this->tomarLock();
    try{
        this->memoriaCompartidaCanchas.leer(cancha,fila,columna);
    }catch(std::exception e){
        this->liberarLock();
        throw(e);
    }
    this->liberarLock();
}

void LockMemoriaCompartidaCanchas::escribir(const TCanchaSerializada &cancha) throw(std::exception){
    this->tomarLock();
    try{
        this->memoriaCompartidaCanchas.escribir(cancha);
    }catch(std::exception e){
        this->liberarLock();
        throw(e);
    }
    this->liberarLock();
}
