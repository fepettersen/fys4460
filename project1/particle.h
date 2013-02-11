#ifndef PARTICLE_H
#define PARTICLE_H
#include <string>
#include <armadillo>
//#include "system.h"

class Particle //: public System
{
public:
    Particle();
    std::string gettype() {return particlename;}
    void settype(std::string newPt) {particlename = newPt;}
    char *getpos();
    char *getvel();
    double getmass() {return mass;}
    void setmass(double newmass) {mass = newmass;}
    void checkpos(double L);
    arma::vec &distanceToAtom(Particle *atom, double L);
    arma::vec r;
    arma::vec v;
    arma::vec F;

private:
    std::string particlename;
    double mass;

};

#endif // PARTICLE_H
