//
// Created by Mariano Hielpos on 9/19/17.
//

#include "Inicializador.h"

static void Inicializador::inicializar(const std::string& archivo) {
    key_t clave=ftok(archivo.c_str(),letra);

}