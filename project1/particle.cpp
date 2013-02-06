#include "particle.h"
using namespace std;
using namespace arma;

Particle::Particle()
    {
    particlename = "type";
    pos = zeros<vec>(3);
    velocity = zeros<vec>(3);
    };
