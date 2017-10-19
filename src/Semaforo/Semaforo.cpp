//
// Created by rafael on 03/10/17.
//

#include "Semaforo.h"

Semaforo::Semaforo(const std::string &nombre, const int valorInicial):valorInicial(valorInicial){
    key_t clave=ftok(nombre.c_str(),'a');
    this->id = semget( clave, 1, 0666 | IPC_CREAT | IPC_EXCL );

    this->inicializar();
}

Semaforo::~Semaforo(){}

Semaforo::Semaforo(const std::string &nombre) {
    key_t clave=ftok(nombre.c_str(),'a');
    this->id = semget( clave, 1, 0666 );
};

int Semaforo::inicializar() const {
    union semnum{
        int val;
        struct semid_ds* buf;
        ushort* array;
    };
    semnum init;
    init.val = this->valorInicial;
    int resultado=semctl(this->id,0,SETVAL,init);
    return resultado;
}

int Semaforo::p() const {
    struct sembuf operacion;
    operacion.sem_num=0;
    operacion.sem_op=-1;
    operacion.sem_flg=SEM_UNDO;
    int resultado=semop(this->id,&operacion,1);
    return resultado;
}

int Semaforo::v() const {
    struct sembuf operacion;
    operacion.sem_num=0;
    operacion.sem_op=1;
    operacion.sem_flg=SEM_UNDO;
    int resultado=semop(this->id,&operacion,1);
    return resultado;
}

int Semaforo::eliminar() const {
    return semctl(this->id,0,IPC_RMID);
}

int Semaforo::getId() {
    return this->id;
}

int Semaforo::obtenerValor() {
    // Structure used in semctl
    union semun {
        int val;					// Value for SETVAL
        struct semid_ds *buf;		// Buffer por IPC_STAT, IPC_SET
        unsigned short *array;		// Array for GETALL, SETALL
        struct seminfo *__buf;		// Buffer for IPC_INFO(Linux specific)
    } arg;

    int val;
    if ((val = semctl(this->id, 0, GETVAL, arg)) == -1) {
        perror("Error obteniendo el valor del semaforo");
    }

    return val;
}
