#include "project1.h"

using namespace std;
using namespace arma;

int main(/*int argc, char** argv*/)
{
    int ncells = 2;
    int counter = 0;
    double T = 1;

    /*some time stuff*/
    double time = 0;
    double Time_end = 0.1;
    double dt = 2e-2;
    System test(ncells,int (Time_end/dt),T);

    /*loop over time and evolve system*/
//    test.output(counter);
    while(time<Time_end){
        test.update_all(dt);
        test.output(counter);
        test.mean_square(counter);
        time += dt;
        counter ++;
    }
    test.outputMeanSquare();
    cout << "it works" << endl;
    return 0;
}

