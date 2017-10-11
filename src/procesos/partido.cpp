
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <Opciones.h>
#include "partido.h"
#include "../utils/sleep.h"



Partido::Partido(participantes p, Logger* logger, Opciones opts, TCanchaSerializada cancha)
  : p_(p), logger(logger), opts_(opts), cancha_(cancha) {
}

participantes Partido::getParticipantes() {
  return p_;
};

void Partido::run() {
  this->logger->info("[Principal] Partido corriendo!");

  srand(getpid());

  int i = 0, j = 0;
  while (i != 3 && j != 3) {
    if (jugarSet()) {
      i++;
    } else {
      j++;
    }
  }

  this->logger->info("[Principal] Partido terminando!");

  int retCode;
  if (i == 3) {
    retCode = (j < 2) ? PRIMER_PAREJA_3 : PRIMER_PAREJA_2;
  } else {
    retCode = (i < 2) ? SEGUNDA_PAREJA_3 : SEGUNDA_PAREJA_2;
  }
  exit(retCode);
}

bool Partido::jugarSet() {
  milisleep(this->opts_.sleepPartido);
  return rand() % 2 == 0;
};

TCanchaSerializada Partido::getCancha() {
  return cancha_;
};
