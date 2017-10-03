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
    unsigned int fila=0;
    unsigned int columna=0;
    pid_t equipo1[JUGADORES_POR_EQUIPO];
    pid_t equipo2[JUGADORES_POR_EQUIPO];
    unsigned int cantidadSets=1;
    unsigned int resultadoSetsEquipo1[NUMERO_MAX_SETS];
    unsigned int resultadoSetsEquipo2[NUMERO_MAX_SETS];

    void init(const unsigned int fila,const unsigned int columna,pid_t* equipo1,pid_t* equipo2,
              const unsigned int cantidadSets,
              const unsigned int* resultadoSetsEquipo1,const unsigned int* resultadoSetsEquipo2){
        this->fila=fila;
        this->columna=columna;
        memcpy(&this->equipo1,equipo1,sizeof(pid_t)*JUGADORES_POR_EQUIPO);
        memcpy(&this->equipo2,equipo2,sizeof(pid_t)*JUGADORES_POR_EQUIPO);
        this->cantidadSets=cantidadSets;
        memcpy(&this->resultadoSetsEquipo1,resultadoSetsEquipo1,sizeof(unsigned int)*NUMERO_MAX_SETS);
        memcpy(&this->resultadoSetsEquipo2,resultadoSetsEquipo2,sizeof(unsigned int)*NUMERO_MAX_SETS);
    }

    std::string toString() {
        std::string retorno = "{Cancha[" + std::to_string(fila) + ',' + std::to_string(columna) + "],";
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

typedef struct JugadorPuntaje{
    pid_t jugador=0;
    unsigned int puntaje=0;
}TJugadorPuntaje;

#endif //TP_CONCURRENTES_2_CUATRI_SERIALIZADOS_H
