//
// Created by rafael on 13/09/17.
//

#ifndef TP_CONCURRENTES_2_CUATRI_SERIALIZADOS_H
#define TP_CONCURRENTES_2_CUATRI_SERIALIZADOS_H
#include <unistd.h>
#include <string>
#include <cstring>
#define JUGADORES_POR_EQUIPO 2
#define NUMERO_MAX_SETS 5

/**
 * Almacena los datos de una cancha con su estado de disponibilidad.
 */
typedef struct CanchaSerializada{
    unsigned int fila=0;
    unsigned int columna=0;
    bool ocupada=false;
    bool inundada=false;
    pid_t proceso=0;
    std::string toString(){
        std::string retorno="{["+std::to_string(fila)+','+std::to_string(columna)+"],";
        if(ocupada){
            retorno+="ocupada,";
        }else{
            retorno+="libre,";
        }
        if(inundada){
            retorno+="inundada,";
        }else{
            retorno+="seca,";
        }
        retorno+="PID:"+std::to_string(proceso);
        retorno+="}";
        return retorno;
    }
    void init(unsigned int fila,unsigned int columna,bool ocupada,bool inundada,pid_t proceso){
        this->fila=fila;
        this->columna=columna;
        this->ocupada=ocupada;
        this->inundada=inundada;
        this->proceso=proceso;
    }
    void setDefault(){
        this->fila=0;
        this->columna=0;
        this->ocupada=false;
        this->inundada=false;
        this->proceso=0;
    }
} TCanchaSerializada;

struct ResultadoSerializado;

/**
 * Almacena los resultados de un partido con los datos de sus jugadores y el puntaje final de los mismos.
 */
typedef struct ResultadoSerializado{
    unsigned int equipo1[JUGADORES_POR_EQUIPO];
    unsigned int equipo2[JUGADORES_POR_EQUIPO];
    unsigned int puntajeEquipo1=0;
    unsigned int puntajeEquipo2=0;

    void init(const unsigned int jugador1Equipo1,const unsigned int jugador2Equipo1,
              const unsigned int jugador1Equipo2,const unsigned int jugador2Equipo2,
              const unsigned int puntajeEquipo1,
              const unsigned int puntajeEquipo2){
        this->equipo1[0]=jugador1Equipo1;
        this->equipo1[1]=jugador2Equipo1;
        this->equipo2[0]=jugador1Equipo2;
        this->equipo2[1]=jugador2Equipo2;
        this->puntajeEquipo1=puntajeEquipo1;
        this->puntajeEquipo2=puntajeEquipo2;
    }

    std::string toString() {
        std::string retorno = "{";
        retorno+=printEquipos()+","+printResultadoPartido()+"}";
        return retorno;
    }

    std::string printEquipos(){
        std::string retorno="(Equipo 1 :"+std::to_string(equipo1[0])+","+std::to_string(equipo1[1])+")";
        retorno+="(Equipo 2 :"+std::to_string(equipo2[0])+","+std::to_string(equipo2[1])+")";
        return retorno;
    }

    std::string printResultadoPartido(){
        std::string retorno = "("+std::to_string(this->puntajeEquipo1)+" a "+std::to_string(puntajeEquipo2)+")";
        return retorno;
    }

} TResultadoSerializado;

struct JugadorPuntaje;

/**
 * Alamacena un par jugador-puntaje
 */
typedef struct JugadorPuntaje{
    unsigned int jugador=0;
    unsigned int puntaje=0;

    void init(unsigned int jugador, unsigned int puntaje) {
        this->jugador=jugador;
        this->puntaje=puntaje;
    }
    /**
     * @return verdadero si el puntaje del primero es menor que el segundo
     */
    bool compare(JugadorPuntaje &jugPunt1,JugadorPuntaje &jugPunt2){
        return jugPunt1.puntaje<jugPunt2.puntaje;
    }
}TJugadorPuntaje;

/*
 * Define la estructura de la memoria compartida persona
 */
typedef struct Persona{
    unsigned int idPersona=0;
    bool enPredio=false;
    bool jugando=false;

    void init(unsigned int idPersona, bool enPredio, bool jugando){
        this->idPersona=idPersona;
        this->enPredio=enPredio;
        this->jugando=jugando;
    }

    void init(Persona& persona){
        this->idPersona=persona.idPersona;
        this->enPredio=persona.enPredio;
        this->jugando=persona.jugando;
    }
}TPersona;

/**
  * @return verdadero si el puntaje del primero es menor que el segundo
*/
static bool compareJugadorPuntaje(TJugadorPuntaje &jugPunt1,TJugadorPuntaje &jugPunt2){
    if(jugPunt1.puntaje<jugPunt2.puntaje)
        return true;
    if(jugPunt1.puntaje==jugPunt2.puntaje){
        return jugPunt1.jugador<jugPunt2.jugador;
    }
    return false;
}

/**
  * @return verdadero si el puntaje del primero es mayor que el segundo
*/
static bool compareJugadorPuntajeReverse(TJugadorPuntaje &jugPunt1,TJugadorPuntaje &jugPunt2){
    if(jugPunt1.puntaje>jugPunt2.puntaje)
        return true;
    if(jugPunt1.puntaje==jugPunt2.puntaje){
        return jugPunt1.jugador<jugPunt2.jugador;
    }
    return false;
}

#endif //TP_CONCURRENTES_2_CUATRI_SERIALIZADOS_H
