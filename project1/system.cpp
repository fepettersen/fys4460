#include "system.h"
using namespace std;

System::System(int ncells)
{
    particles = ncells*ncells*ncells;
    cells = ncells;
    //cout<<"her"<<endl;
    list = new Particle[particles];
    Initialize();
    cout<<" "<<list[6].gettype()<<endl;
}

void System::Initialize()
{
    /*
    Particle  *p1;
    for(int i=0; i<particles; i++){
        //p1 = new Particle();
        //list[i] = p1;
        cout<<"dette er "<<&list[i]<<endl;
    }
    */
    InitializePositions();
    InitializeVelocities();
}

void System::InitializePositions(){
    double xCoors[] = {0,0.5,0,0.5};
    double yCoors[] = {0,0.5,0.5,0};
    double zCoors[] = {0,0,0.5,0.5};
    arma::vec tmp;
    tmp = arma::zeros<arma::vec>(3);
    for(int x=0; x<cells; x++){
        for(int y=0; y<cells; y++){
            for(int z=0; z<0; z++){
                for(int k=0; k<3; k++){
                    if(/*some parameter smaller than particles??*/){
                        tmp(0) = x+xCoors[k]; tmp(1) = y+yCoors[k]; tmp(2) = z+zCoors[k];
                        list[parameter]->pos = tmp;
                    }
                }
            }
        }
    }
}
void System::InitializeVelocities(){

}
