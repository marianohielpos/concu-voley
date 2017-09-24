//
// Created by rafael on 23/09/17.
//

#ifndef CONCU_VOLEY_MEMORIACOMPARTIDARESULTADOS_H
#define CONCU_VOLEY_MEMORIACOMPARTIDARESULTADOS_H
#include "Serializados.h"
#include "MemoriaCompartida.h"
#include <list>
#define ARCHIVO_MEMORIA_RESULTADOS "/bin/bash"
#define CARACTER_MEMORIA_RESULTADOS 'b'
#define CARACTER_MEMORIA_CANTIDAD_RESULTADOS 'c'

class MemoriaCompartidaResultados {

private:

    MemoriaCompartida<TResultadoSerializado> resultados;

    MemoriaCompartida<unsigned int> cantidadResultados;

    unsigned int cantidadMaxResultados=0;

public:

    /**
     * Pre:-
     * Post: Se reserva la memoria compartida.
     *
     * @throws: En caso de no poder reserva la memoria compartida se lanza una excepción.
     */
    MemoriaCompartidaResultados(unsigned int maxCantidadResultados) throw(std::exception);

    ~MemoriaCompartidaResultados(){
        this->resultados.liberar();
        this->cantidadResultados.liberar();
    }

    bool push(const TResultadoSerializado& resultado);

    void cleanMemoria();

    /*
     * Post: la destrucción de la lista retornada queda a cargo del usuario.
     */
    std::list<TResultadoSerializado>* readAll();

private:

    void inicializarMemoriaResultados() throw(std::exception);

    void inicializarCantidadResultados() throw(std::exception);
};


#endif //CONCU_VOLEY_MEMORIACOMPARTIDARESULTADOS_H
