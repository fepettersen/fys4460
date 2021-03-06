#include "project2.h"

using namespace std;
using namespace arma;

int main(/*int argc, char** argv*/)
{
    int thermostat = 1;
    int ncells = 20;
    int counter = 0;
    double T_kelvin = 101.9498;
    double T = T_kelvin/119.8;

    /*some time stuff*/
    double time = 0;
    double Time_end = 1.0;
    double dt = 5e-3;
    System test(ncells,int (Time_end/dt),T);

    /*loop over time and evolve system*/
    while(time<Time_end){
        test.update_all(dt);
        if(time < dt*100 && thermostat){
            test.BerendsenThermostat();
//            test.AndersenThermostat(dt);
        }
        test.output(counter);
        test.mean_square(counter);
        time += dt;
        counter ++;
    }
    test.outputMeanSquare();
    cout << "simulation finished" << endl;
    return 0;
}

