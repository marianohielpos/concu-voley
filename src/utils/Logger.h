//
// Created by Mariano Hielpos on 9/10/17.
//

#ifndef TP_CONCURRENTES_2_CUATRI_LOG_H
#define TP_CONCURRENTES_2_CUATRI_LOG_H


#include <LockFile.h>
#include <string>
#include <iostream>

class Logger {

private:

    LockFile *lock;

public:

    Logger ( std::string nombre );

    ~Logger();

    void log(std::string texto);

};


#endif //TP_CONCURRENTES_2_CUATRI_LOG_H
