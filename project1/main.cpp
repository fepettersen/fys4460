#include "project1.h"

using namespace std;
using namespace arma;


int main(/*int argc, char** argv*/)
{
    int ncells = 20;
    double T_kelvin = 119.8*1.5;
    double T = T_kelvin/119.8;

    /*some time stuff*/
    double Time_end = 2.5;
    double dt = 5e-3;

    int timesteps = int (Time_end/dt);

    System MySys(ncells,timesteps,T);

    /*loop over time and evolve system*/
//    MySys.Thermalize(170,dt,true,true);
//    MySys.Thermalize(200,dt,true,true);
    MySys.SimulateFlow(dt,true);
    cout << "simulation finished" << endl;
    return 0;
}

