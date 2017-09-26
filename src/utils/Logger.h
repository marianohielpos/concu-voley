//
// Created by Mariano Hielpos on 9/10/17.
//

#ifndef TP_CONCURRENTES_2_CUATRI_LOG_H
#define TP_CONCURRENTES_2_CUATRI_LOG_H


#include <LockFile.h>
#include <string>
#include <iostream>
#include <map>

class Logger {

private:

    std::map<std::string, int> levels = {
            {"debug", 10},
            {"info", 20},
            {"debug", 30},
            {"warning", 40},
            {"error", 50}
    };

    LockFile *lock = NULL;

    bool timestamp = true;

    bool pid = true;

    std::string logLevel = "info";

    std::string generarMensaje(std::string mensaje, std::string nivel);

    void imprimirMensaje(std::string mensaje);

    void escribirAArchivo(std::string mensaje);

    void escribirAConsola(std::string mensaje);

public:

    Logger ( std::string nombreArchivo, std::string nivel);

    ~Logger();

    void info(std::string mensaje);

    void debug(std::string mensaje);

    void warning(std::string mensaje);

    void error(std::string mensaje);
};


#endif //TP_CONCURRENTES_2_CUATRI_LOG_H
