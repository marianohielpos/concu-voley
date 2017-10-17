//
// Created by rafael on 24/09/17.
//

#include "LockMemoriaCompartidaCanchas.h"
#include "signal.h"
#include <list>

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

std::list<pid_t> LockMemoriaCompartidaCanchas::inundarFilasDeCanchas(int fila) {
    return this->inundarDesinundar(fila, true);
}

std::list<pid_t> LockMemoriaCompartidaCanchas::desinundarFilasDeCanchas(int fila) {
    return this->inundarDesinundar(fila, false);
}

std::list<pid_t> LockMemoriaCompartidaCanchas::inundarDesinundar(int fila, bool inundar) {

    TCanchaSerializada cancha;

    std::list<pid_t> procesosAfectados;

    this->tomarLock();
    try{
        for (int columna = 0; columna < this->memoriaCompartidaCanchas.getColumnas(); ++columna) {
            this->memoriaCompartidaCanchas.leer(cancha,fila,columna);

            if (inundar) {
                cancha.inundada = true;

                if (cancha.proceso != 0) {
                    procesosAfectados.push_back(cancha.proceso);
                    kill(cancha.proceso, SIGINT);
                }

            } else {
                cancha.inundada = false;
            }

            this->memoriaCompartidaCanchas.escribir(cancha);
        }
    }catch(std::exception e){
        this->liberarLock();
        throw(e);
    }
    this->liberarLock();

    return procesosAfectados;
}

bool LockMemoriaCompartidaCanchas::obtenerCanchaLibre(TCanchaSerializada &cancha) {
    bool canchaEncontrada = false;
    int i = 0, j = 0;

    while(!canchaEncontrada) {
        leer(cancha, j, i);
        if (!cancha.ocupada && !cancha.inundada) {
            canchaEncontrada = true;
        } else {
            if (++i == memoriaCompartidaCanchas.getColumnas()) {
                i = 0;
                j++;
            }
        }
        if (j == memoriaCompartidaCanchas.getFilas()) {
            break;
        }
    }

    return canchaEncontrada;
}

bool LockMemoriaCompartidaCanchas::hayCanchaLibre() {

    TCanchaSerializada cancha;

    return this->obtenerCanchaLibre(cancha);

}
