#include <iostream>
#include <getopt.h>
#include "utils/Opciones.h"

#define CANTIDAD_MINIMA_DE_JUGADORES 10

Opciones parsearParametros (int argc, char *argv[]) {
    Opciones opciones;

    int opt;
    while ((opt = getopt(argc, argv, "hdj:s:")) != -1) {
        switch (opt) {
            case 'd':
                opciones.debug = true;
                break;
            case 'j':
                opciones.jugadores = (unsigned int) std::stoul(optarg);
                break;
            case 's':
                opciones.sleep = (unsigned int) std::stoul(optarg);
                break;
            case 'h':
                std::cout << "Uso: [-d] [-j cantidadDeJugadores] [-s sleepTime]\n";
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

    std::cout << opciones.jugadores << std::endl;
    std::cout << opciones.debug << std::endl;
    std::cout << opciones.logName << std::endl;
    std::cout << opciones.sleep << std::endl;

    return 0;
}