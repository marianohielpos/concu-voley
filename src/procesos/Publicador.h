//
// Created by rafael on 04/10/17.
//

#ifndef CONCU_VOLEY_PUBLICADOR_H
#define CONCU_VOLEY_PUBLICADOR_H


#include <EventHandler.h>
#include <PublicadorDeEstadisticas.h>
#include <Opciones.h>
#include <Logger.h>

class Publicador{

private:

    Opciones opts_;
    Logger* logger_;
    PublicadorDeEstadisticas publicador_;

public:

    Publicador(Opciones opts, Logger* logger) throw(std::exception);

    void run();

    ~Publicador();

};

#endif //CONCU_VOLEY_PUBLICADOR_H
