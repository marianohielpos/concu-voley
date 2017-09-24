//
// Created by rafael on 12/09/17.
//

#ifndef TP_CONCURRENTES_2_CUATRI_MEMORIACOMPARTIDACANCHAS_H
#define TP_CONCURRENTES_2_CUATRI_MEMORIACOMPARTIDACANCHAS_H
#include "Serializados.h"
#include "MemoriaCompartida.h"
#define ARCHIVO_MEMORIA_CANCHAS "/bin/bash"
#define CARACTER_MEMORIA_CANCHAS 'a'
/*
 * Una instancia de esta clase representa una porción de memoria compartida asignada
 * a colección matricial de TCachaSerializada sobre la cual se puede leer o escribir.
 * */
class MemoriaCompartidaCanchas{

private:

    MemoriaCompartida<TCanchaSerializada> memoria;
    int filas,columnas;

public:

    /**
     * Pre:-
     * Post: Se reserva la memoria compartida.
     *
     * @throws: En caso de no poder reserva la memoria compartida se lanza una excepción.
     */
    MemoriaCompartidaCanchas(const unsigned int filas, const unsigned int columnas) throw(std::exception);

    ~MemoriaCompartidaCanchas(){
        this->memoria.liberar();
    }

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

    unsigned int calcularOffset(const unsigned int fila,const unsigned int columna) const;

    void checkFilaColumna(const unsigned int fila, const unsigned int columna) throw(std::exception);
};

#endif //TP_CONCURRENTES_2_CUATRI_MEMORIACOMPARTIDACANCHAS_H
