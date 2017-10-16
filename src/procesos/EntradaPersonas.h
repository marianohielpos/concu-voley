//
// Created by rafael on 15/10/17.
//

#ifndef CONCU_VOLEY_ENTRADAPERSONAS_H
#define CONCU_VOLEY_ENTRADAPERSONAS_H
#include "AdminEntradaPersonas.h"
#include "Opciones.h"
/**
 * Una instancia de esta clase implementa la funcionalidad de entrada de personas al predio.
 */
class EntradaPersonas {

    Opciones opts_;
    AdminEntradaPersonas adminEntradaPersonas;

public:

    /**
     *
     * @throws: exception en caso de no poder acceder a las memorias compartidas asociadas.
     */
    EntradaPersonas(Opciones opts) throw(std::exception);

    /*
     * Corre la entrada de personas hasta que el programa finalice.
     */
    void run();

    ~EntradaPersonas();

};


#endif //CONCU_VOLEY_ENTRADAPERSONAS_H
