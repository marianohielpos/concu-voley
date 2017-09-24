//
// Created by rafael on 12/09/17.
//

#ifndef TP_CONCURRENTES_2_CUATRI_MEMORIACOMPARTIDA_H
#define TP_CONCURRENTES_2_CUATRI_MEMORIACOMPARTIDA_H
#define SHM_OK                  0
#define ERROR_FTOK              -1
#define ERROR_SHMGET            -2
#define ERROR_SHMAT              -3

#include <string>
#include <sys/shm.h>
#include <cstring>
#include "Serializados.h"

template <class T> class MemoriaCompartida {

private:
    int shmId;
    T*  ptrDatos;
    int cantidadProcesosAdosados() const;

public:
    MemoriaCompartida();
    ~MemoriaCompartida();
    int crear(const std::string& archivo,const char letra,unsigned int longitud);
    void liberar();
    void escribir(const T& dato,int offset);
    void leer(T& buffer,int offset) const;

};


template <class T> MemoriaCompartida<T>::MemoriaCompartida() :shmId(0),ptrDatos(NULL){}

template <class T> MemoriaCompartida<T>::~MemoriaCompartida() {}

template <class T> int MemoriaCompartida<T>::crear(const std::string& archivo,const char letra,unsigned int longitud){
    key_t clave=ftok(archivo.c_str(),letra);
    if(clave == -1)
        return ERROR_FTOK;
    else {
        this->shmId=shmget(clave,sizeof(T)*longitud,0644|IPC_CREAT);
        if(this->shmId == -1){
            return ERROR_SHMGET;
        }
        else{
            void* ptrTemporal=shmat(this->shmId,NULL,0);
            if(ptrTemporal == (void*)-1){
                return ERROR_SHMAT;
            }else {
                this->ptrDatos=static_cast<T*>(ptrTemporal);
                return SHM_OK;
            }
        }
    }
}

template<class T> void MemoriaCompartida<T>::liberar(){
    shmdt (static_cast<void*>(this->ptrDatos));
    int procAdosados = this->cantidadProcesosAdosados();
    if(procAdosados == 0){
        shmctl(this->shmId,IPC_RMID,NULL);
    }
}

template<class T> void MemoriaCompartida<T>::escribir(const T& dato,int offset){
    memcpy(&this->ptrDatos[offset],&dato,sizeof(T));
}

template<class T> void MemoriaCompartida<T>::leer(T &buffer,int offset) const{
    memcpy(&buffer,&ptrDatos[offset],sizeof(buffer));
}

template <class T> int MemoriaCompartida<T>::cantidadProcesosAdosados() const {
    shmid_ds estado;
    shmctl(this->shmId,IPC_STAT,&estado);
    return estado.shm_nattch;
}
#endif //TP_CONCURRENTES_2_CUATRI_MEMORIACOMPARTIDA_H
