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

    /*some time stuff*/
    System test(ncells);
    /*loop over time and evolve system*/
    test.output();
    cout << "it works" << endl;
    return 0;
}

