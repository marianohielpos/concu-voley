#include <iostream>
#include <getopt.h>
#include <Logger.h>
#include <Opciones.h>
#include <MemoriaCompartidaCanchas.h>
#include "procesos/principal.h"


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
                break;
            case 'b':
                opciones.sleepPartido = (unsigned int) std::stoul(optarg);
                break;
            case 'e':
                opciones.sleepPublicador = (unsigned int) std::stoul(optarg);
                break;
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
            case 's':
                opciones.archivoSalida = std::string(optarg);
                break;
            case 'h':
                std::cout << "Uso:\n"
                          << "\n"
                          << "Concu_voley [Opciones]\n"
                          << "\n"
                          << "Opciones:\n"
                          << "-j      Cantidad de jugadores máxima para jugar en el torneo (default: 15)\n"
                          << "-p      Cantidad de partidos que puede jugar un jugador como máximo (default: 3)\n"
                          << "-f      Cantidad de filas de canchas (default: 5)\n"
                          << "-c      Cantidad de columnas de canchas (default: 5)\n"
                          << "\n"
                          << "-l      Archivo de log (default: ninguno, se escribe a stdout)\n"
                          << "-k      Nivel de log (default: info)\n"
                          << "\n"
                          << "-a      Cantidad de milisegundos que duerme la marea entre los checkeos si\n"
                          << "        subir o no (default: 200)\n"
                          << "-b      Cantidad de milisegundos que duerme un partido entre los sets (default: 200)\n"
                          << "-e      Cantidad de milisegundos que duerme el publicador entre cada escritura\n"
                          << "        de resultados (default: 200)\n"
                          << "-g      Cantidad de milisegundos que pasa entre la entrada de los jugadores\n"
                          << "        nuevos (default: 200)\n"
                          << "\n"
                          << "-s      Archivo a escribir los resultados (default: /tmp/webvoley.html)\n"
                          << std::endl;
                exit(0);

        }

        if (opciones.jugadores < opciones.jugadoresParaTorneo) {
            fprintf(stderr, "Número incorrecto de jugadores");
            exit(EXIT_FAILURE);
        }
    }
    return opciones;
}


int main(int argc, char *argv[]) {

    Opciones opciones = parsearParametros(argc, argv);

    Logger::setInstance(opciones);

    MainProcess mp(opciones);

    mp.run();

    Logger::deleteInstance();

    return 0;
}
