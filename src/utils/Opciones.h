#ifndef TP1CONCURRENTES_OPCIONES_H
#define TP1CONCURRENTES_OPCIONES_H
#include <string>

using std::string;

typedef struct {
    bool debug = false;
    unsigned int jugadores = 15;
    unsigned int partidos = 3;
    string logName = "";
    string logLevel = "info";
    unsigned int sleepPartido = 200;
    unsigned int sleepMarea = 200;
    unsigned int sleepJugadores = 200;
    unsigned int sleepPublicador = 200;
    unsigned int filas = 5;
    unsigned int columnas = 5;

    unsigned int chanceSalirPredio = 10;
    unsigned int chanceEntrarPredio = 30;
    string archivoSalida = "/tmp/webvoley.html";
} Opciones;

#endif //TP1CONCURRENTES_OPCIONES_H
