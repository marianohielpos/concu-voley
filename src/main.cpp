#include <iostream>
#include <getopt.h>
#include <Logger.h>
#include <Opciones.h>
#include <MemoriaCompartidaCanchas.h>
#include "procesos/principal.h"

#define CANTIDAD_MINIMA_DE_JUGADORES 10

Opciones parsearParametros (int argc, char *argv[]) {
    Opciones opciones;

    int opt;
    while ((opt = getopt(argc, argv, "hdj:s:p:l:k:a:b:c:e:f:g:")) != -1) {
        switch (opt) {
            case 'l':
                opciones.logName = std::string(optarg);
                break;
            case 'k':
                opciones.logLevel = std::string(optarg);
                break;
            case 'd':
                opciones.debug = true;
                break;
            case 'j':
                opciones.jugadores = (unsigned int) std::stoul(optarg);
                break;
            case 'a':
                opciones.sleepMarea = (unsigned int) std::stoul(optarg);
            case 'b':
                opciones.sleepPartido = (unsigned int) std::stoul(optarg);
            case 'e':
                opciones.sleepPublicador = (unsigned int) std::stoul(optarg);
            case 'g':
                opciones.sleepJugadores = (unsigned int) std::stoul(optarg);
                break;
            case 'f':
                opciones.filas = (unsigned int) std::stoul(optarg);
                break;
            case 'c':
                opciones.columnas = (unsigned int) std::stoul(optarg);
                break;
            case 'p':
                opciones.partidos = (unsigned int) std::stoul(optarg);
                break;
            case 'h':
                std::cout << "Uso: [-d] [-j cantidadDeJugadores] [-s sleepTime]"
                          << "[-p partidosPorJugador]"
                          << "[-l nombreDelLog]"
                          << "[-k nivelDelLog [debug, info]]"
                          << std::endl;
                exit(0);

        }

        if (opciones.jugadores < CANTIDAD_MINIMA_DE_JUGADORES) {
            fprintf(stderr, "Número incorrecto de jugadores");
            exit(EXIT_FAILURE);
        }
    }
    return opciones;
}


int main(int argc, char *argv[]) {

    Opciones opciones = parsearParametros(argc, argv);

    Logger logger = Logger(opciones.logName, opciones.logLevel);

    MainProcess mp(opciones, &logger);

    mp.run();

    return 0;
}
