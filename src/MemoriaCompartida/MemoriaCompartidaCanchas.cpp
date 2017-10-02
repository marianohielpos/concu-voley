//
// Created by rafael on 13/09/17.
//
#include "MemoriaCompartidaCanchas.h"

MemoriaCompartidaCanchas::MemoriaCompartidaCanchas(const unsigned int filas, const unsigned int columnas)
                                                    throw(std::exception){
    this->filas=filas;
    this->columnas=columnas;
    if(this->memoria.crear(ARCHIVO_MEMORIA_CANCHAS,CARACTER_MEMORIA_CANCHAS,filas*columnas)!=SHM_OK){
        throw(std::exception());
    };
}

void MemoriaCompartidaCanchas::escribir(const TCanchaSerializada& cancha) throw(std::exception){
    this->lock.tomarLock();
    checkFilaColumna(cancha.fila,cancha.columna);
    this->memoria.escribir(cancha, this->calcularOffset(cancha.fila, cancha.columna));
    this->lock.liberarLock();
}

void MemoriaCompartidaCanchas::leer(TCanchaSerializada &cancha,const unsigned int fila,const unsigned int columna) throw(std::exception){
    this->lock.tomarLock();
    checkFilaColumna(fila,columna);
    this->memoria.leer(cancha, this->calcularOffset(fila, columna));
    this->lock.liberarLock();
}

unsigned int MemoriaCompartidaCanchas::calcularOffset(const unsigned int fila, const unsigned int columna) const {
    return fila*columnas+columna;
}

void MemoriaCompartidaCanchas::checkFilaColumna(const unsigned int fila,const unsigned int columna) throw(std::exception){
    if ((fila>=filas)||(columna>=columnas)){
        throw(std::exception());
    }
}