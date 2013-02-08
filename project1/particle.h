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
    arma::vec pos;
    arma::vec velocity;
private:
    std::string particlename;
    double mass;

};

#endif // PARTICLE_H
