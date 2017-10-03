//
// Created by rafael on 25/09/17.
//

#ifndef CONCU_VOLEY_MEMORIACOMPARTIDAJUGADORES_H
#define CONCU_VOLEY_MEMORIACOMPARTIDAJUGADORES_H
#include "MemoriaCompartida.h"
#include <list>
#include "Serializados.h"
#define ARCHIVO_MEMORIA_COMPARTIDA_JUGADORES "/bin/bash"
#define CARACTER_MEMORIA_COMPARTIDA_JUGADORES 'd'
#define CARACTER_MEMORIA_CANTIDAD_JUGADORES 'e'

class MemoriaCompartidaJugadores {

    MemoriaCompartida<TJugadorPuntaje> jugadores;

    MemoriaCompartida<unsigned int> cantidadJugadores;

    unsigned int cantidadMaxJugadores=0;

public:

    /**
     * Pre:-
     * Post: Se reserva la memoria compartida.
     *
     * @throws: En caso de no poder reserva la memoria compartida se lanza una excepción.
     */
    MemoriaCompartidaJugadores(unsigned int maxCantidadJugadores) throw(std::exception);

    ~MemoriaCompartidaJugadores(){
        this->jugadores.liberar();
        this->cantidadJugadores.liberar();
    }

    bool push(const TJugadorPuntaje& puntaje);

    void cleanMemoria();

    /*
     * Post: la destrucción de la lista retornada queda a cargo del usuario.
     */
    std::list<TJugadorPuntaje>* readAll();

private:

    void inicializarMemoriaJugadorPuntaje() throw(std::exception);

    void inicializarCantidadJugadores() throw(std::exception);
};


#endif //CONCU_VOLEY_MEMORIACOMPARTIDAJUGADORES_H
