#include "project1.h"
#include "particle.h"
#include "cell.h"
#include <string>
#include <vector>
#ifndef BALLE_H
#define BALLE_H

class System
{
public:
    /*Methods*/
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
    void accept();
    void setupCells();

    /*values*/
    Particle *particle;
    Cell *cell;
    double r_cut;
private:
    /*Methods*/
    arma::vec force(arma::vec dr);

    /*values*/
    int particles;
    int cells;
    double b;   //lattice constant
    double L;
};

#endif // BALLE_H
