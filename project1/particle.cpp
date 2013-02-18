


#include "project1.h"

using namespace std;
using namespace arma;

Particle::Particle()
    {
    particlename = "Ar";
    mass = 1.0; //atomic units *1.66053886e-27
    r = zeros<vec>(3);
    v = zeros<vec>(3);
    F = zeros<vec>(3);
    r_tmp = zeros<vec>(3);
    cellID = 99;
    };
char *Particle::getpos()
{
    char* buffer = new char[60];
    sprintf(buffer, "%.12g  %.12g  %.12g", r(0), r(1), r(2));
    return buffer;
}

char *Particle::getvel()
{
    char* buffer = new char[60];
    sprintf(buffer, "%.12g  %.12g  %.12g", v(0), v(1), v(2));
    return buffer;
}

void Particle::checkpos(double L){
    r(0) = fmod(r(0),L) + L*(r(0) < 0);
    r(1) = fmod(r(1),L) + L*(r(1) < 0);
    r(2) = fmod(r(2),L) + L*(r(2) < 0);
}

vec3 Particle::distanceToAtom(Particle *atom, double L) {
    vec3 dr = atom->r-r;
    for(int i=0;i<3;i++) {
        if(dr(i) > L/2.0){
            dr(i) -= L;
        }
        else if(dr(i)< -L/2.0){
            dr(i) += L;
        }
    }

//    for(int i=0;i<3;i++){
//        dr(i) = (dr(i)/fabs(dr(i)))*max(dr(i),0.8);
//    }
    return dr;
}
vec3 Particle::NewdistanceToAtom(Particle *atom, double cell_length, double L) {
    vec3 dr = atom->r-r;
    for(int i=0;i<3;i++) {
        if(fabs(dr(i))> 2*cell_length){
        dr(i) = fmod(r(i) +100*cell_length,cell_length);
        }
    }

//    for(int i=0;i<3;i++){
//        dr(i) = (dr(i)/fabs(dr(i)))*max(dr(i),0.8);
//    }
    return dr;
}
