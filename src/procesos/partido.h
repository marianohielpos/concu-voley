#ifndef __PARTIDO_H__
#define __PARTIDO_H__


#include <array>
#include <Logger.h>
#include "Opciones.h"
#include "../MemoriaCompartida/Serializados.h"

typedef std::array<int, 4> participantes;

#define PRIMER_PAREJA_3 10
#define SEGUNDA_PAREJA_3 11
#define PRIMER_PAREJA_2 12
#define SEGUNDA_PAREJA_2 13

class Partido {

participantes p_;
TCanchaSerializada cancha_;

bool jugarSet();

protected:

    Logger* logger;

    Opciones opts_;

public:
  Partido(participantes p, Logger* logger, Opciones opts_, TCanchaSerializada cancha);

  void run();

  participantes getParticipantes();

  TCanchaSerializada getCancha();

};

#endif
