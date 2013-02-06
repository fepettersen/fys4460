#include "project1.h"
#include "particle.h"
#include <string>
#include <vector>
#ifndef BALLE_H
#define BALLE_H

class System
{
public:
    System(int ncells);
    int getParticles(){return particles;}
    void setBalle(int newParticles){particles = newParticles;}
    void Initialize();
    void InitializePositions();
    void InitializeVelocities();
    //std::vector<Particle*> list;    //find a better solution
    Particle *list;
private:
    int particles;
    int cells;

};

#endif // BALLE_H
