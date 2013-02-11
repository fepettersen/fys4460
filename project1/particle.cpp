#include "particle.h"
using namespace std;
using namespace arma;

Particle::Particle()
    {
    particlename = "Ar";
    mass = 39.948*1.66053886e-27;
    r = zeros<vec>(3);
    v = zeros<vec>(3);
    };
char *Particle::getpos()
{
    char* buffer = new char[60];
    sprintf(buffer, "%g  %g  %g", r(0), r(1), r(2));
    return buffer;
}

char *Particle::getvel()
{
    char* buffer = new char[60];
    sprintf(buffer, "%g  %g  %g", v(0), v(1), v(2));
    return buffer;
}

void Particle::checkpos(double L){
    r(0) = fmod(r(0)+ 100*L,L);
    r(1) = fmod(r(1)+ 100*L,L);
    r(2) = fmod(r(2)+ 100*L,L);
}

vec& Particle::distanceToAtom(Particle *atom, double L) {
    vec dr = r-atom->r;

    for(int i=0;i<3;i++) {
        if(dr(i) > L/2.0)
            dr(i) -= L;
        else if(dr(i)< -L / 2.0)
            dr(i) += L;
    }
    return dr;
}
/*
  This is what we want to have after implementing neighbour-lists
vec Particle::calculateForce(){
    for(int j=0;j<neighbours;j++){
        if(j!=i){
            F +=neighbour[i].distanceToAtom(particle[j]);
        }
    }
}
*/
