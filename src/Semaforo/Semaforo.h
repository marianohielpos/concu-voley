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
    Semaforo(const std::string &nombre);

    ~Semaforo();

    int p() const; //decrementa

    int v() const; //incrementa

    int obtenerValor();

    int eliminar() const;

    int getId();
};


#endif //CONCU_VOLEY_SEMAFORO_H
