#ifndef __PARTIDO_H__
#define __PARTIDO_H__


#include <array>

typedef std::array<int, 4> participantes;


class Partido {

participantes p_;

public:
  Partido(participantes p);

  void run();

  participantes getParticipantes();
};

#endif
