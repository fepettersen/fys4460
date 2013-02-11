#include "project1.h"
#include "particle.h"
//#include "integrator_md.h"
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
    void output(int nr);
    void update(double dt);
    void boundary_pos();
    arma::vec grad_U(int i);
    //std::vector<Particle*> list;    //find a better solution
    Particle *particle;
private:
    int particles;
    int cells;
    double b;   //lattice constant
    double L;
    arma::vec force(arma::vec dr);
    //Integrator_md *integrator;

};

#endif // BALLE_H
