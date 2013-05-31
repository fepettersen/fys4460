#include "project1.h"

using namespace std;
using namespace arma;


int main(/*int argc, char** argv*/)
{
    int ncells = 12;
    double T_kelvin = 300;//119.8*2.0;
    double T = T_kelvin/119.8;

    /*some time stuff*/
    double Time_end = 12.5;
    double dt = 2e-3;

//    int timesteps = int (Time_end/dt);
    int timesteps = 2500;

    System MySys(ncells,timesteps,T);
//        MySys.Thermalize(1500,dt,true,true);
//    MySys.Spheres(14,20,30);
    /*loop over time and evolve system*/

    MySys.SimulateFlow(dt,true);
    cout << "simulation finished" << endl;
    return 0;
}

