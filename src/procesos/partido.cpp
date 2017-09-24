
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "partido.h"
#include "../utils/sleep.h"



Partido::Partido(participantes p, Logger* logger) : p_(p) {
  this->logger = logger;
}

participantes Partido::getParticipantes() {
  return p_;
};

void Partido::run() {
  this->logger->info("Partido corriendo!");

  srand(getpid());

  int i = 0, j = 0;
  while (i != 3 && j != 3) {
    if (jugarSet()) {
      i++;
    } else {
      j++;
    }
  }

  this->logger->info("Partido terminando!");

  int retCode;
  if (i == 3) {
    retCode = (j < 2) ? PRIMER_PAREJA_3 : PRIMER_PAREJA_2;
  } else {
    retCode = (i < 2) ? SEGUNDA_PAREJA_3 : SEGUNDA_PAREJA_2;
  }
  exit(retCode);
}

bool Partido::jugarSet() {
  milisleep(100);
  return rand() % 2 == 0;
};
