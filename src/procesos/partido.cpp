
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "partido.h"


Partido::Partido(participantes p) : p_(p) {
}

participantes Partido::getParticipantes() {
  return p_;
};

void Partido::run() {
  std::cout << "Partido corriendo! " << getpid() << std::endl;
  srand(getpid());

  int i = 0, j = 0;
  while (i != 3 && j != 3) {
    if (jugarSet()) {
      i++;
    } else {
      j++;
    }
  }

  std::cout << "Partido terminando! " << getpid() << std::endl;

  int retCode;
  if (i == 3) {
    retCode = (j < 2) ? PRIMER_PAREJA_3 : PRIMER_PAREJA_2;
  } else {
    retCode = (i < 2) ? SEGUNDA_PAREJA_3 : SEGUNDA_PAREJA_2;
  }
  exit(retCode);
}

bool Partido::jugarSet() {
  struct timespec tim;
  tim.tv_sec = 0;
  tim.tv_nsec = 100 * 1000000L;
  nanosleep(&tim, NULL);

  return rand() % 2 == 0;
};
