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
    arma::vec3 distanceToAtom(Particle *atom, double L);
    arma::vec3 r;
    arma::vec3 v;
    arma::vec3 F;
    arma::vec3 r_tmp;

private:
    std::string particlename;
    double mass;

};

#endif // PARTICLE_H
