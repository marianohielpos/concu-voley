#ifndef TP1CONCURRENTES_OPCIONES_H
#define TP1CONCURRENTES_OPCIONES_H
#include <string>

using std::string;

typedef struct {
    bool debug = false;
    unsigned int jugadores = 15;
    unsigned int partidos = 3;
    string logName = "";
    unsigned int sleep = 5;
} Opciones;

#endif //TP1CONCURRENTES_OPCIONES_H
