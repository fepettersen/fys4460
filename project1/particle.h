#ifndef PARTICLE_H
#define PARTICLE_H
#include <string>

class Particle
{
public:
    Particle(std::string pt);
    std::string gettype() {return particlename;}
    void settype(std::string newPt) {particlename = newPt;}
private:
    std::string particlename;

};

#endif // PARTICLE_H