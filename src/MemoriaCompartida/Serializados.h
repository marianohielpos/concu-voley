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

typedef struct ResultadoSerializado{
    pid_t equipo1[JUGADORES_POR_EQUIPO];
    pid_t equipo2[JUGADORES_POR_EQUIPO];
    unsigned int cantidadSets=1;
    unsigned int resultadoSetsEquipo1[NUMERO_MAX_SETS];
    unsigned int resultadoSetsEquipo2[NUMERO_MAX_SETS];

    void init(pid_t* equipo1,pid_t* equipo2,
              const unsigned int cantidadSets,
              const unsigned int* resultadoSetsEquipo1,
              const unsigned int* resultadoSetsEquipo2){
        memcpy(&this->equipo1,equipo1,sizeof(pid_t)*JUGADORES_POR_EQUIPO);
        memcpy(&this->equipo2,equipo2,sizeof(pid_t)*JUGADORES_POR_EQUIPO);
        this->cantidadSets=cantidadSets;
        memcpy(&this->resultadoSetsEquipo1,resultadoSetsEquipo1,sizeof(unsigned int)*NUMERO_MAX_SETS);
        memcpy(&this->resultadoSetsEquipo2,resultadoSetsEquipo2,sizeof(unsigned int)*NUMERO_MAX_SETS);
    }

    void init(const pid_t jugador1Equipo1,const pid_t jugador2Equipo1,
              const pid_t jugador1Equipo2,const pid_t jugador2Equipo2,
              const unsigned int cantidadSets,
              const unsigned int set1eq1,const unsigned int set1eq2,
              const unsigned int set2eq1,const unsigned int set2eq2,
              const unsigned int set3eq1,const unsigned int set3eq2,
              const unsigned int set4eq1,const unsigned int set4eq2,
              const unsigned int set5eq1,const unsigned int set5eq2){
        this->equipo1[0]=jugador1Equipo1;
        this->equipo1[1]=jugador2Equipo1;
        this->equipo2[0]=jugador1Equipo2;
        this->equipo2[1]=jugador2Equipo2;
        this->cantidadSets=cantidadSets;
        this->resultadoSetsEquipo1[0]=set1eq1;
        this->resultadoSetsEquipo2[0]=set1eq2;
        this->resultadoSetsEquipo1[1]=set2eq1;
        this->resultadoSetsEquipo2[1]=set2eq2;
        this->resultadoSetsEquipo1[2]=set2eq1;
        this->resultadoSetsEquipo2[2]=set2eq2;
        this->resultadoSetsEquipo1[3]=set3eq1;
        this->resultadoSetsEquipo2[3]=set3eq2;
        this->resultadoSetsEquipo1[4]=set4eq1;
        this->resultadoSetsEquipo2[4]=set4eq2;
        this->resultadoSetsEquipo1[5]=set5eq1;
        this->resultadoSetsEquipo2[5]=set5eq2;
    }

    std::string toString() {
        std::string retorno = "{";
        retorno+=printEquipos()+","+printResultadosSets()+"}";
        return retorno;
    }

    std::string printEquipos(){
        std::string retorno="(Equipo 1 :"+std::to_string(equipo1[0])+","+std::to_string(equipo1[1])+")";
        retorno+="(Equipo 2 :"+std::to_string(equipo2[0])+","+std::to_string(equipo2[1])+")";
        return retorno;
    }

    std::string printResultadosSets(){
        std::string retorno = "(";
        for(int set=0;set<cantidadSets;set++) {
            retorno+= "Set "+std::to_string(set+1)+": "+std::to_string(resultadoSetsEquipo1[set]) + " a " +
                                  std::to_string(resultadoSetsEquipo2[set]);
            if(set<(cantidadSets-1)){
                retorno+=" - ";
            }
        }
        retorno+=")";
        return retorno;
    }

} TResultadoSerializado;

struct JugadorPuntaje;

typedef struct JugadorPuntaje{
    pid_t jugador=0;
    unsigned int puntaje=0;

    /**
     * @return verdadero si el puntaje del primero es menor que el segundo
     */
    bool compare(JugadorPuntaje &jugPunt1,JugadorPuntaje &jugPunt2){
        return jugPunt1.puntaje<jugPunt2.puntaje;
    }
}TJugadorPuntaje;

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
