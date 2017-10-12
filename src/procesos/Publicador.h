//
// Created by rafael on 04/10/17.
//

#ifndef CONCU_VOLEY_PUBLICADOR_H
#define CONCU_VOLEY_PUBLICADOR_H


#include <EventHandler.h>
#include <PublicadorDeEstadisticas.h>
#include <Opciones.h>
#include <Logger.h>

/**
 * Una instancia de esta clase se encarga de actualizar una paǵina web de acuerdo al contenido
 * de la memoria compartida de resultados y jugador-puntaje.
 */
class Publicador{

private:

    Opciones opts_;
    PublicadorDeEstadisticas publicadorEstadisticas_;

public:

    /**
     *
     * @throws: exception en caso de no poder acceder a las memorias compartidas asociadas.
     */
    Publicador(Opciones opts) throw(std::exception);

    /*
     * Corre el publicador hasta que el programa finalice.
     */
    void run();

    ~Publicador();

};

#endif //CONCU_VOLEY_PUBLICADOR_H
