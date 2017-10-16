//
// Created by rafael on 14/10/17.
//

#ifndef CONCU_VOLEY_MEMORIACOMPARTIDAPERSONAS_H
#define CONCU_VOLEY_MEMORIACOMPARTIDAPERSONAS_H
#define ARCHIVO_MEMORIA_COMPARTIDA_PERSONAS "/bin/bash"
#define CARACTER_MEMORIA_COMPARTIDA_PERSONAS 'f'
#include "Serializados.h"
#include "MemoriaCompartida.h"
#include <list>
#include <jugador.h>
#include <vector>

/**
 * Una instancia de esta clase permite realizar reserva, lecturas y escrituras sobre
 * una memoria compartida estructurada bajo el tipo TPersona
 */
class MemoriaCompartidaPersonas {

    MemoriaCompartida<TPersona> personas;

    unsigned int cantidadPersonas;

    unsigned int capacidadPredio;

public:
    /*
     * Se reserva la memoria compartida.
     *
     * @throws: En caso de no poder reserva la memoria compartida se lanza una excepción.
     */
    MemoriaCompartidaPersonas(unsigned int cantidadPersonas,unsigned int capacidadPredio)
                            throw(std::exception);

    ~MemoriaCompartidaPersonas(){
        this->personas.liberar();
    }

    /*
     * Retorna la lista de personas leídas de la memoria compartida dada.
     * La destrucción de la lista retornada queda a cargo del usuario.
     */
    std::list<TPersona>* readAll();

    /*
     * Retorna la lista de personas leídas de la memoria compartida dada.
     * La destrucción de la lista retornada queda a cargo del usuario.
     */
    std::list<TPersona>* readAllFueraDelPredio();

    /**
     * @return la cantidad de presonas dentro del predio
     */
    unsigned int cantidadPersonasDentroDelPredio();

    /**
     * @return verdadero si la capacidad máxima del predio es mayor que la cantidad de personas
     * dentro del predio.
     */
    bool capacidadPredioAgotada();

    /*
     * Retorna la lista de personas leídas de la memoria compartida dada.
     * La destrucción de la lista retornada queda a cargo del usuario.
     */
    std::list<TPersona>* readAllDentroDelPredio();

    /*
     * Retorna la lista de personas leídas de la memoria compartida dada.
     * La destrucción de la lista retornada queda a cargo del usuario.
     */
    std::list<TPersona>* readAllEnPredioJugando();

    /*
     * Retorna la lista de personas leídas de la memoria compartida dada.
     * La destrucción de la lista retornada queda a cargo del usuario.
     */
    std::list<TPersona>* readAllEnPredioEsperandoParaJugar();

    std::vector<Jugador>* readAllEnPredioEsperandoParaJugarAsVector();


    /**
     * libera los recursos de memoria compartida asociados a la instancia.
     */
    void liberar();

    void cleanMemoria();

    /**
    * Se actualiza el contenido de la memoria de acuerdo al parámetro dado.
    * @throws: lanza una excepción en caso de no poder acceder a la memoria dada.
    */
    void escribir(const TPersona& persona) throw(std::exception);

private:

    void inicializarMemoria() throw(std::exception);
};


#endif //CONCU_VOLEY_MEMORIACOMPARTIDAPERSONAS_H
