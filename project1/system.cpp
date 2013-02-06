#include "system.h"
using namespace std;

System::System(int ncells)
{
    particles = 4*ncells*ncells*ncells;
    cells = ncells;
    b = 5.260e-10;
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
    double xCoors[] = {0,0.5*b,0,0.5*b};
    double yCoors[] = {0,0.5*b,0.5*b,0};
    double zCoors[] = {0,0,0.5*b,0.5*b};
    arma::vec tmp;
    tmp = arma::zeros<arma::vec>(3);
    int counter = 0;
    for(int x=0; x<cells; x++){
        for(int y=0; y<cells; y++){
            for(int z=0; z<0; z++){
                for(int k=0; k<3; k++){
                    counter ++;
                    if(counter<particles){
                        tmp(0) = x+xCoors[k]; tmp(1) = y+yCoors[k]; tmp(2) = z+zCoors[k];
                        list[counter].pos = tmp;
                    }
                }
            }
        }
    }
}
void System::InitializeVelocities(){

}
void System::output(){
    /*outfile is an ofstram-object letting us open a file
    **u is an armadillo-object containing the solution at time n
    **n is the timestep number
    **scheme is an integer telling what scheme is used to obtain the solution
    **N is the size of the array*/
    ofstream outfile;
    outfile.open("test.xyz");
    for(int i=0;i<particles;i++){
        outfile<<list[i].gettype()<< list[i].pos<<list[i].velocity<< endl;
    }
    outfile.close();
}
