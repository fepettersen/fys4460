#include <iostream>
#include <project1.h>
#include "particle.h"
#include "system.h"
using namespace std;
using namespace arma;

int main(/*int argc, char** argv*/)
{
    int ncells = 8;//atoi(argv[1]);
    double T = 100;
    double k_B = 1.38e-23;
    int counter = 0;

    /*some time stuff*/
    double time = 0; double Time_end = 1.0;
    double dt = 5e-3;
    System test(ncells);
    /*loop over time and evolve system*/
    while(time<Time_end){
        test.update(dt);
//        test.accept();
        test.output(counter);
        time += dt;
        counter ++;
    }

    cout << "it works" << endl;
    return 0;
}

