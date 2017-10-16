//
// Created by rafael on 15/10/17.
//

#ifndef CONCU_VOLEY_ADMINSALIDAPERSONAS_H
#define CONCU_VOLEY_ADMINSALIDAPERSONAS_H
#include "LockMemoriaCompartidaPersonas.h"
#include "Opciones.h"

/**
 * Una instancia de esta clase implementa la funcionalidad de salida de personas
 * del predio. El acceso a memoria compartida se hace bajo mecanismo de lock.
 */
class AdminSalidaPersonas {

    LockMemoriaCompartidaPersonas lockMemoriaCompartidaPersonas;

public:

    /**
     * crea la instancia inicializando la memoria compartida de personas con
     * la cantidad de máxima de personas afuera del predio
     */
    AdminSalidaPersonas(Opciones opciones) throw(std::exception);

    /**
     * destruye la instancia liberando recursos como locks y memoria compartida.
     */
    ~AdminSalidaPersonas(){
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
     * intenta ingresar una persona.
     */
    void retirarPersona();
};


#endif //CONCU_VOLEY_ADMINSALIDAPERSONAS_H
