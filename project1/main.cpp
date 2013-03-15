#include "project1.h"

using namespace std;
using namespace arma;

double timediff(double time1, double time2){
    // This function returns the elapsed time in milliseconds
    return ((time2 - time1)*1000)/CLOCKS_PER_SEC;
}




char *timeRemaining(double timediff,int totaltimesteps, int completedsteps){
    int secs = timediff*(totaltimesteps-completedsteps)/1000;
    int hour = secs/3600;
    secs %= 3600;
    int min = secs/60;
    secs %= 60;
    char* buffer = new char[60];
    sprintf(buffer, "%d h %d min  %d sec",hour ,min , secs);
    return buffer;
}

int main(/*int argc, char** argv*/)
{
    int thermostat = 0;
    int ncells = 20;
    int counter = 0;
    double T_kelvin = 125.79;
    double T = T_kelvin/119.8;

    /*some time stuff*/
    double time = 0;
    double Time_end = 10.0;
    double dt = 5e-3;
    double start = 0;
    double stop = 0;
    int timesteps = int (Time_end/dt);
    bool output = true;

    System test(ncells,timesteps,T);
//    test.Spheres(20,20,30);
    test.Input();
    test.AdjustDensity(2.0);
    /*loop over time and evolve system*/

    while(time<Time_end){
        start = clock();
        test.update_all(dt);
        if(counter < 150 && thermostat){
            test.BerendsenThermostat();
//            test.AndersenThermostat(dt);
        }
//        if(counter == 170){
//            test.Spheres(20,20,30);
//            cout<<"HEI"<<endl;
//        }
        test.output(counter);
        test.mean_square(counter);
        stop = clock();
        if(output){
            cout<< "step "<<counter<<" of "<<timesteps<<" : approx "<<timeRemaining(timediff(start,stop),timesteps,counter)<<" remaining"<<endl;
        }
        time += dt;
        counter ++;
    }
    test.outputMeanSquare();

    cout << "simulation finished" << endl;
    return 0;
}

