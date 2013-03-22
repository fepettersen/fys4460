#ifndef PARTICLE_H
#define PARTICLE_H

/*
  Each particle object has:
    a vec3 position -r- which defines where it is in the system
    a vec3 velocity -v- which defines its velocity
    a vec3 force -F- which defines the sum of forces on the particle
    a vec3 position -r_tmp- which is used to make the update go smoothly
    a vec3 position -r0- which defines it's original position
    a vec3 position -delta_r- which is used to calculate the total displacement of the particle
    a cell number which is simply an int ID telling which cell it started out in
    a mass which is not used (=1)
    and a name used for output as of now
  */
class Particle //: public System
{
public:
    Particle();
    std::string gettype() {return particlename;}
    void settype(std::string newPt) {particlename = newPt;}
    char *getpos();
    char *getvel();
    char *getForce();
    double getmass() {return mass;}
    void setmass(double newmass) {mass = newmass;}
    void checkpos(double L);
    char *distanceMoved();
    arma::vec3 distanceToAtom(Particle *atom, double L);
    void Drift(int direction, double size);
    void getInfo(char *buffer);

    arma::vec3 r;
    arma::vec3 v;
    arma::vec3 F;
    arma::vec3 r_tmp;
    arma::vec3 r0;
    arma::vec3 delta_r;
    int cellID;
    int sysIndex;
    int inttype;

private:
    std::string particlename;
    double mass;


};

#endif // PARTICLE_H
