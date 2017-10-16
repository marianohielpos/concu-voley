//
// Created by rafael on 14/10/17.
//

#ifndef CONCU_VOLEY_ADMINENTRADAPERSONAS_H
#define CONCU_VOLEY_ADMINENTRADAPERSONAS_H
#include "LockMemoriaCompartidaPersonas.h"
#include "Opciones.h"
#include <queue>

/**
 * Una instancia de esta clase implementa la funcionalidad de ingreso de personas
 * al predio. El acceso a memoria compartida se hace bajo mecanismo de lock.
 */
class AdminEntradaPersonas {

    LockMemoriaCompartidaPersonas lockMemoriaCompartidaPersonas;
    std::queue<TPersona> cola;

public:

    /**
     * crea la instancia inicializando la memoria compartida de personas con
     * la cantidad de máxima de personas afuera del predio
     */
    AdminEntradaPersonas(Opciones opciones) throw(std::exception);

    /**
     * destruye la instancia liberando recursos como locks y memoria compartida.
     */
    ~AdminEntradaPersonas(){
        this->liberarRecursos();
    }

    /**
     * Intenta ingresar una nueva persona al predio.
     * El éxito dependera de la cantidad de persona que hay en el mismo.
     */
    void update();

    /**
     * libera los recursos asociados a la instancia, como ser memoria compartida y
     * locks.
     */
    void liberarRecursos();

private:

    /**
     * si la cola esta vacía la llena.
     */
    void llenarCola();

    /**
     * intenta ingresar una persona.
     */
    void ingresarPersona();
};


#endif //CONCU_VOLEY_ADMINENTRADAPERSONAS_H
