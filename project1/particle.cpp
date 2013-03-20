


#include "project1.h"

using namespace std;
using namespace arma;

Particle::Particle()
    {
    particlename = "Ar";
    mass = 1.0; //atomic units *1.66053886e-27
    r = zeros(3);
    v = zeros(3);
    F = zeros(3);
    delta_r = zeros(3);
    r_tmp = zeros(3);
    cellID = 99;
    sysIndex = -1;
    inttype = -1;
    };
char *Particle::getpos()
{
    /*for pretty output*/
    char* buffer = new char[60];
    sprintf(buffer, "%.12g  %.12g  %.12g", r(0), r(1), r(2));
    return buffer;
}

char *Particle::getvel()
{
    /*for pretty output*/
    char* buffer = new char[60];
    sprintf(buffer, "%.12g  %.12g  %.12g", v(0), v(1), v(2));
    return buffer;
}
char *Particle::getForce()
{
    /*for pretty output*/
    char* buffer = new char[60];
    sprintf(buffer, "%.12g  %.12g  %.12g", F(0), F(1), F(2));
    return buffer;
}
void Particle::checkpos(double L){
    /*ensures particles stay in a reasonable place*/
    r(0) = fmod(r(0),L) + L*(r(0) < 0);
    r(1) = fmod(r(1),L) + L*(r(1) < 0);
    r(2) = fmod(r(2),L) + L*(r(2) < 0);
}

vec3 Particle::distanceToAtom(Particle *atom, double L) {
    /*distance between the atom you are and another*/
    vec3 dr = atom->r-r;
    for(int i=0;i<3;i++) {
        if(dr(i) > L/2.0){
            dr(i) -= L;
        }
        else if(dr(i)< -L/2.0){
            dr(i) += L;
        }
    }
    return dr;
}

char *Particle::distanceMoved(){
    /*for pretty output*/
    char* buffer = new char[60];
    sprintf(buffer, "%.12g  %.12g  %.12g", delta_r(0), delta_r(1), delta_r(2));
    return buffer;
}

void Particle::Drift(int direction, double size){
    F(direction) += size;
}
