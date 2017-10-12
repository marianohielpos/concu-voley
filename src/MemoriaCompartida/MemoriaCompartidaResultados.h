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

/**
 * Una instancia de esta clase permite insertar y leer resultados en una memoria compartida
 * dada para este tipo de dato.
 */
class MemoriaCompartidaResultados {

private:

    MemoriaCompartida<TResultadoSerializado> resultados;

    MemoriaCompartida<unsigned int> cantidadResultados;

    unsigned int cantidadMaxResultados=0;

public:

    /**
     * Se reserva la memoria compartida.
     *
     * @throws: En caso de no poder reserva la memoria compartida se lanza una excepción.
     */
    MemoriaCompartidaResultados(unsigned int maxCantidadResultados) throw(std::exception);

    ~MemoriaCompartidaResultados(){
        this->resultados.liberar();
        this->cantidadResultados.liberar();
    }

    bool push(const TResultadoSerializado& resultado);

    /*
     * Se limpia la memoria compartida asociada.
     */
    void cleanMemoria();

    /*
     * Se retorna una lista con el cotenido de la memoria de resultados. La destrucción
     * de la lista retornada queda a cargo del usuario.
     */
    std::list<TResultadoSerializado>* readAll();

    /**
     * libera los recursos de memoria compartida asociados a la instancia.
     */
    void liberar();

private:

    void inicializarMemoriaResultados() throw(std::exception);

    void inicializarCantidadResultados() throw(std::exception);
};


#endif //CONCU_VOLEY_MEMORIACOMPARTIDARESULTADOS_H
