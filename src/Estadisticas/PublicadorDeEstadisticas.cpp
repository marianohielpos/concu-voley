//
// Created by rafael on 17/09/17.
//

#include <iostream>
#include "PublicadorDeEstadisticas.h"

PublicadorDeEstadisticas::PublicadorDeEstadisticas(Opciones opts) throw(std::exception) :
                        lockResultados(opts.jugadores * opts.partidos),
                        lockJugadores(opts.jugadores), publicador(opts.archivoSalida) {
}

PublicadorDeEstadisticas::~PublicadorDeEstadisticas() {
}

void PublicadorDeEstadisticas::update() {
    std::list<TResultadoSerializado>* listaResultados=this->lockResultados.readAll();
    std::list<TJugadorPuntaje>* listaJugadores=this->lockJugadores.readAll();
    publicador.update(listaResultados,listaJugadores);
    delete(listaResultados);
    delete(listaJugadores);
}

void PublicadorDeEstadisticas::liberarRecursos() {
    this->update();
    this->lockJugadores.liberarMemoria();
    this->lockResultados.liberarMemoria();
}
