#include <iostream>
#include <project1.h>
#include "particle.h"
#include "system.h"
using namespace std;
using namespace arma;

int main(/*int argc, char** argv*/)
{
    int nparticles = 8;//atoi(argv[1]);
    System test(nparticles);
    /*
    vector<Particle*> list;
    Particle  *p1;

    for(int i=0; i<nparticles; i++){
        p1 = new Particle("Ar");
        list.push_back(p1);
    }
    */

    cout << "it works" << endl;
    return 0;
}

