#include "project1.h"

#ifndef BALLE_H
#define BALLE_H

class Balle
{
public:
    Balle();
    int getBalle(){return baller;}
    void setBalle(int newBalle){baller = newBalle;}

private:
    int baller;

};

#endif // BALLE_H
