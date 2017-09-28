#ifndef __PARTIDO_H__
#define __PARTIDO_H__


#include <array>
#include <Logger.h>
#include "Opciones.h"

typedef std::array<int, 4> participantes;

#define PRIMER_PAREJA_3 10
#define SEGUNDA_PAREJA_3 11
#define PRIMER_PAREJA_2 12
#define SEGUNDA_PAREJA_2 13

class Partido {

participantes p_;

bool jugarSet();

protected:

    Logger* logger;

    Opciones opts_;

public:
  Partido(participantes p, Logger* logger, Opciones opts_);

  void run();

  participantes getParticipantes();


};

#endif
