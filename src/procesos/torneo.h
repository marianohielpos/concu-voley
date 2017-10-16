
#ifndef __TORNEO_H__
#define __TORNEO_H__

#include <vector>
#include <map>
#include "../utils/Opciones.h"
#include "../ipc/EventHandler.h"
#include "../modelo/jugador.h"
#include "../Estadisticas/ConexionPubEstad.h"
#include "../MemoriaCompartida/LockMemoriaCompartidaCanchas.h"
#include "../MemoriaCompartida/Serializados.h"
#include "partido.h"
#include "LockMemoriaCompartidaPersonas.h"
#define JUGADORES_PARA_TORNEO 10

/**
 * una instancia de clase implementa la funcionalidad de llevar a cabo un torneo
 * realizando los accesos a memoria compartida bajo mecanismos de lock y salvando
 * en el log las operaciones realizadas.
 */
class Torneo {

    Opciones opts_;

    std::vector<Jugador> jugadores_;

    std::map<pid_t, Partido> partidos_;

    ConexionPubEstad conexion_;

    LockMemoriaCompartidaCanchas memoriaCanchas_;

    LockMemoriaCompartidaPersonas memoriaCompartidaPersonas;

    bool sePuedeArmarPartido();

    bool partidosCorriendo();

    bool lanzarPartido();

    /**
    * Determina los participantes necesarios para llevar a cabo un partido.
    * @returns verdadero si puede hallarlos.
    */
    bool siguientesParticipantes(participantes& p);

    void finalizarPartido(pid_t pidPartido, int status);

    void guardarResultado(pid_t pidPartido, int status);

    void liberarCancha(pid_t pidPartido);

    void finalizarTorneo();

    void liberarRecursos();

    void inicializarVectorJugadores(unsigned int maxCantPersonas);

public:

    Torneo(Opciones opts);

    void run();

};

#endif
