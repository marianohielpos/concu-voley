//
// Created by rafael on 17/09/17.
//

#ifndef CONCU_VOLEY_STATISTICSMANAGER_H
#define CONCU_VOLEY_STATISTICSMANAGER_H
#include "PublicadorWeb.h"
#include "LockMemoriaCompartidaResultados.h"
#include "LockMemoriaCompartidaJugadores.h"
#include "../utils/Opciones.h"

/**
 * Una instancia de esta clase lee los resultados de partidos y pares jugador-puntaje
 * (guardados en las memorias compartidas correspondientes bajo mecanismo de lock) para
 * luego actualizar el contenido de la página web correspondiente.
 */
class PublicadorDeEstadisticas {

private:

    LockMemoriaCompartidaResultados lockResultados;

    LockMemoriaCompartidaJugadores lockJugadores;

    PublicadorWeb publicador;

public:

    /**
     * @throws exception en caso de no poder acceder a las memorias correspondientes
     */
    PublicadorDeEstadisticas(Opciones opts) throw(std::exception);
    /**
     * Lee el contenido de las memorias compartidas asociadas bajo mecanismo de lock
     * actualizando el contenido de la página web.
     */
    void update();

    ~PublicadorDeEstadisticas();

    /**
     * libera los recursos de memoria compartida asociados a la instancia.
     */
    void liberarRecursos();
};


#endif //CONCU_VOLEY_STATISTICSMANAGER_H
