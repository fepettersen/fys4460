#include "project1.h"

#ifndef BALLE_H
#define BALLE_H

class System
{
public:
    System(int nparticles);
    int getParticles(){return particles;}
    void setBalle(int newParticles){particles = newParticles;}

private:
    int particles;

};

#endif // BALLE_H
