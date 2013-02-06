#include "particle.h"
using namespace std;
using namespace arma;

Particle::Particle(string pt)
    {
    particlename = pt;
    pos = zeros<vec>(3);
    velocity = zeros<vec>(3);
    };
