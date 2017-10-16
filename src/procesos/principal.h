
#ifndef __MAIN_PROCESS_H__
#define __MAIN_PROCESS_H__


#include <MemoriaCompartidaCanchas.h>
#include <EventHandler.h>
#include <jugador.h>
#include "../utils/Opciones.h"
#include "Logger.h"
#include <vector>
/**
 * Una instancia de esta clase se encarga de crear los procesos asociados a las clases Publicador y
 * Marea llamando a los métodos update de ambos inmediatemente luego de su creación.
 */
class MainProcess {

Opciones opts_;

private:
    pid_t pidPublicador;
    pid_t pidMarea;
    pid_t pidTorneo;
    pid_t pidEntradaPersonas;
    pid_t pidSalidaPersonas;

public:

    MainProcess(Opciones opts);

    ~MainProcess();

    /**
     * se matan los procesos hijos correspondientes al publicador, la marea, el torneo, entrada y
     * salida de personas.
     */
    void matarProcesosHijos();

    /**
     * se inicia la corrida del proceso.
     */
    void run();

    /**
     * se matan los procesos hijos correspondientes al publicador, la marea, el torneo, entrada y
     * salida de personas debido a una interrupción.
     */
    void matarProcesosHijosPorInterrupcion();

private:

    /**
     * crea la instancia de Entrada Personas llamando inmediatamente a su método run
     */
    void iniciarEntradaPersonas();

    /**
     * crea la instancia de Salida Personas llamando inmediatamente a su método run
     */
    void iniciarSalidaPersonas();

    /**
     * crea la instancia de publicador llamando inmediatamente a su método run
     */
    void iniciarPublicador();

    /**
     * crea la instancia de marea llamando inmediatamente a su método run
     */
    void iniciarMarea();

    /**
     * crea la instancia de torneo llamando inmediatamente a su método run
     */
    void iniciarTorneo();

};

class Terminador : public EventHandler {

    MainProcess& m_;

public:

    Terminador(MainProcess& m_);

    virtual int handleSignal (int signum);

    ~Terminador();
};

#endif // MAIN_PROCESS_H

