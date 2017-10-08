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

/**
 * Una instancia de clase permite actualizar y leer el contenido de una memoria compartida
 * con datos del tipo TJugadorPuntaje.
 */
class MemoriaCompartidaJugadores {

    MemoriaCompartida<TJugadorPuntaje> jugadores;

    MemoriaCompartida<unsigned int> cantidadJugadores;

    unsigned int cantidadMaxJugadores=0;

public:

    /*
     * Se reserva la memoria compartida.
     *
     * @throws: En caso de no poder reserva la memoria compartida se lanza una excepción.
     */
    MemoriaCompartidaJugadores(unsigned int maxCantidadJugadores) throw(std::exception);

    ~MemoriaCompartidaJugadores(){
        this->jugadores.liberar();
        this->cantidadJugadores.liberar();
    }

    /**
     * Inserta el par jugador-puntaje en la memoria.
     * @return verdadero en caso de poder realizar la inserción, falso caso contrario.
     */
    bool push(const TJugadorPuntaje& puntaje);

    /**
     * Limpia la memoria compartida asociada de contenido.
     */
    void cleanMemoria();

    /*
     * Retorna la lista de pares jugador-puntaje leídas de la memoria compartida dada.
     * La destrucción de la lista retornada queda a cargo del usuario.
     */
    std::list<TJugadorPuntaje>* readAll();

    void liberar();

private:

    void inicializarMemoriaJugadorPuntaje() throw(std::exception);

    void inicializarCantidadJugadores() throw(std::exception);
};


#endif //CONCU_VOLEY_MEMORIACOMPARTIDAJUGADORES_H
