//
// Created by rafael on 13/09/17.
//
#include "MemoriaCompartidaCanchas.h"

MemoriaCompartidaCanchas::MemoriaCompartidaCanchas(const unsigned int filas, const unsigned int columnas)
                                                    throw(std::exception){
    this->filas=filas;
    this->columnas=columnas;
}

void MemoriaCompartidaCanchas::inicializar() {
    if(this->memoria.crear(ARCHIVO_MEMORIA_CANCHAS,CARACTER_MEMORIA_CANCHAS,filas*columnas)!=SHM_OK){
        throw(std::exception());
    };
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            TCanchaSerializada cancha;
            cancha.init(i, j, false, false, 0);
            escribir(cancha);
        }
    }
}

void MemoriaCompartidaCanchas::escribir(const TCanchaSerializada& cancha) throw(std::exception){
    checkFilaColumna(cancha.fila,cancha.columna);
    this->memoria.escribir(cancha, this->calcularOffset(cancha.fila, cancha.columna));
}

void MemoriaCompartidaCanchas::leer(TCanchaSerializada &cancha,const unsigned int fila,const unsigned int columna) throw(std::exception){
    checkFilaColumna(fila,columna);
    this->memoria.leer(cancha, this->calcularOffset(fila, columna));
}

unsigned int MemoriaCompartidaCanchas::calcularOffset(const unsigned int fila, const unsigned int columna) const {
    return fila*columnas+columna;
}

void MemoriaCompartidaCanchas::checkFilaColumna(const unsigned int fila,const unsigned int columna) throw(std::exception){
    if ((fila>=filas)||(columna>=columnas)){
        throw(std::exception());
    }
}

void MemoriaCompartidaCanchas::liberar() {
    this->memoria.liberar();
}

int MemoriaCompartidaCanchas::getColumnas() const {
    return columnas;
}

void MemoriaCompartidaCanchas::setColumnas(int columnas) {
    MemoriaCompartidaCanchas::columnas = columnas;
}

int MemoriaCompartidaCanchas::getFilas() const {
    return filas;
}

void MemoriaCompartidaCanchas::setFilas(int filas) {
    MemoriaCompartidaCanchas::filas = filas;
}
