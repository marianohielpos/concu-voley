//
// Created by rafael on 03/10/17.
//

#ifndef CONCU_VOLEY_SEMAFORO_H
#define CONCU_VOLEY_SEMAFORO_H
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaforo {

private:

    int id;

    int valorInicial;

    int inicializar() const;

public:

    Semaforo(const std::string& nombre,const int valorInicial);

    ~Semaforo();

    int p() const; //decrementa

    int v() const; //incrementa

    void eliminar() const;
};


#endif //CONCU_VOLEY_SEMAFORO_H
