//
// Created by rafael on 15/10/17.
//

#ifndef CONCU_VOLEY_SALIDAPERSONAS_H
#define CONCU_VOLEY_SALIDAPERSONAS_H
#include "AdminSalidaPersonas.h"
#include "Opciones.h"

/**
 * Una instancia de esta clase implementa la funcionalidad de salida de personas al predio.
 */
class SalidaPersonas {

    Opciones opts_;
    AdminSalidaPersonas adminSalidaPersonas;

public:

    /**
     *
     * @throws: exception en caso de no poder acceder a las memorias compartidas asociadas.
     */
    SalidaPersonas(Opciones opts) throw(std::exception);

    /*
     * Corre la salida de personas hasta que el programa finalice.
     */
    void run();

    ~SalidaPersonas();

};


#endif //CONCU_VOLEY_SALIDAPERSONAS_H
