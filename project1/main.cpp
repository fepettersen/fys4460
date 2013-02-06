#include <iostream>
#include <project1.h>
#include "particle.h"
using namespace std;

int main(int argc, char** argv)
{
    int nparticles = 8;//atoi(argv[1]);
    //Particle **partlist = new *Particle partlist[nparticles];
    vector<Particle*> list;
    Particle  *p1;
    for(int i=0;i<nparticles;i++)
    {
        p1 = new Particle("Ar");
        list.push_back(p1);
    }


    cout << "it works" << endl;
    /*printballe->settype("hesteballe");
    cout << "Hello World!" << printballe->gettype() << " " << printballe->ballenr << endl;
    */
    return 0;
}

