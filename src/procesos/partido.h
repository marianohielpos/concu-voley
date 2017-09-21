#ifndef __PARTIDO_H__
#define __PARTIDO_H__


#include <array>

typedef std::array<int, 4> participantes;

#define PRIMER_PAREJA_3 10
#define SEGUNDA_PAREJA_3 11
#define PRIMER_PAREJA_2 12
#define SEGUNDA_PAREJA_2 13

class Partido {

participantes p_;

bool jugarSet();

public:
  Partido(participantes p);

  void run();

  participantes getParticipantes();
};

#endif
