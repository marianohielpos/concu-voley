
#include <iostream>
#include <time.h>
#include <unistd.h>
#include "partido.h"


Partido::Partido(participantes p) : p_(p) {
}

void Partido::run() {
  std::cout << "Partido corriendo! " << getpid() << std::endl;
  struct timespec tim;
  tim.tv_sec = 0;
  tim.tv_nsec = 500 * 1000000L;
  nanosleep(&tim, NULL);
  std::cout << "Partido terminando! " << getpid() << std::endl;
  exit(0);
}
