//
// Created by rafael on 04/10/17.
//

#ifndef CONCU_VOLEY_PUBLICADOR_H
#define CONCU_VOLEY_PUBLICADOR_H


#include <EventHandler.h>
#include <PublicadorDeEstadisticas.h>

class Publicador{

private:

    PublicadorDeEstadisticas* publicador = NULL;

public:

    Publicador(const unsigned maxCantidadResultados,
               const unsigned maxCantidadJugadores) throw(std::exception);

    void run();

    ~Publicador();

};

#endif //CONCU_VOLEY_PUBLICADOR_H
