#include "particle.h"
using namespace std;
using namespace arma;

Particle::Particle()
    {
    particlename = "Ar";
    mass = 39.948*1.66053886e-27;
    pos = zeros<vec>(3);
    velocity = zeros<vec>(3);
    };
char *Particle::getpos()
{
    char* buffer = new char[60];
    sprintf(buffer, "%g  %g  %g", pos(0), pos(1), pos(2));
    return buffer;
}

char *Particle::getvel()
{
    char* buffer = new char[60];
    sprintf(buffer, "%g  %g  %g", velocity(0), velocity(1), velocity(2));
    return buffer;
}
