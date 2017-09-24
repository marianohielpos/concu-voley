//
// Created by Mariano Hielpos on 9/23/17.
//

#ifndef CONCU_VOLEY_MAREA_H
#define CONCU_VOLEY_MAREA_H
#include "Logger.h"

class Marea {

private:
    Logger* logger;

public:
    Marea(Logger* logger);

    void run();

};


#endif //CONCU_VOLEY_MAREA_H
