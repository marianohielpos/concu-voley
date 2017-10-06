//
// Created by rafael on 18/09/17.
//

#ifndef CONCU_VOLEY_CONEXIONPUBESTAD_H
#define CONCU_VOLEY_CONEXIONPUBESTAD_H
#include "LockMemoriaCompartidaResultados.h"
#include "LockMemoriaCompartidaJugadores.h"

/*
 * Una instancia de esta clase permite insertar resultados y pares jugador-puntaje en un sector de
 * memoria compartida bajo mecanismo de lock.
 * */
class ConexionPubEstad {

private:

    LockMemoriaCompartidaResultados lockMemoriaCompartidaResultados;

    LockMemoriaCompartidaJugadores lockMemoriaCompartidaJugadores;

public:
    /**
     * @throws exception en caso de no poder crearse correctamente la instancia.
     */
    ConexionPubEstad(unsigned int maxCantidadResultados,
                     unsigned int maxCantidadJugadoresPuntaje)
                    throw(std::exception);

    ~ConexionPubEstad();

    /**
     * @param resultadoSerializado
     * @return verdadero si se pudo agregar el resultado, falso caso contrario.
     */
    bool addResultado(TResultadoSerializado &resultadoSerializado);

    /**
     * @param jugadorPuntaje
     * @return verdadero si se pudo agregar el par jugador-puntaje, falso caso contrario.
     */
    bool addJugadorPuntaje(TJugadorPuntaje &jugadorPuntaje);

};


#endif //CONCU_VOLEY_CONEXIONPUBESTAD_H
