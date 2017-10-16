//
// Created by rafael on 14/10/17.
//

#ifndef CONCU_VOLEY_LOCKMEMORIACOMPARTIDAPERSONAS_H
#define CONCU_VOLEY_LOCKMEMORIACOMPARTIDAPERSONAS_H
#define ARCHIVO_LOCK_MEMORIA_COMPARTIDA_PERSONAS "/tmp/lockMemoriaCompartidaPersonas.tmp"
#include "MemoriaCompartidaPersonas.h"
#include <fcntl.h>
#include <iostream>
#include <list>
#include <queue>
#include <map>
#include "participantes.h"

class Partido;

/**
 * Permite acceder a la memoria compartida de personas bajo mecanismos de lock.
 */
class LockMemoriaCompartidaPersonas {
private:

    struct flock fl;

    int fd;

    std::string nombre;

    MemoriaCompartidaPersonas* memoriaCompartidaPersonas=NULL;

public:

    /**
     * @throws: exception en caso de no poder acceder a la memoria asociada.
     */
    LockMemoriaCompartidaPersonas(unsigned int cantidadPersonas, unsigned int capacidadPredio)
                                throw(std::exception);

    ~LockMemoriaCompartidaPersonas();

    /**
     * Se accede a la memoria bajo mecanismos de lock.
     * Limpia la memoria compartida asociada de contenido.
     */
    void cleanMemoria();

    /**
     * Se accede a la memoria bajo mecanismos de lock.
     * @return una lista con el contenido de la memoria compartida. La destrucción de la
     * misma queda a cargo del usuario.
     */
    std::list<TPersona>* readAll();

    /**
     * libera los recursos de memoria compartida asociados a la instancia.
     */
    void liberarRecursos();

    /**
     * llena la cola con personas que están fuera del predio
     */
    void llenarCola(std::queue<TPersona>& cola);

    /**
     * intenta ingresar una persona al predio
     */
    bool ingresarPersona(TPersona& persona);

    /**
     * intenta retirar una persona del predio
     */
    void retirarPersona();

    bool obtenerParticipantes(participantes& p, std::map<pid_t,Partido>& partidos_);

    bool sePuedenObtenerParticipantes(std::map<pid_t,Partido>& partidos_);

    /**
     * marca como jugando bajo locks
     */
    void marcarComoEsperandoJugar(participantes& p);

    unsigned int cantidadEnPredio();

private:

    int tomarLock ();

    int liberarLock ();

    void inicializarLock();

    std::list<TPersona>* doReadAll();

    /**
     * Accede a la memoria bajo mecanismo de lock.
     * @throws: lanza una excepción en caso de no poder acceder a la memoria de la persona dada.
     */
    void escribir(const TPersona& persona) throw(std::exception);

    unsigned int calcularRandom();

    bool calcularSalida();

    void marcarEstadoJugando(participantes &p, bool estado);

    /**
     * sin meceanismos de lock
     */
    void doMarcarEstadoJugando(unsigned int idPersona, bool estado);

    bool doObtenerParticipantes(participantes& p, std::map<pid_t,Partido>& partidos_);
};


#endif //CONCU_VOLEY_LOCKMEMORIACOMPARTIDAPERSONAS_H
