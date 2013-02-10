#include "system.h"
using namespace std;
using namespace arma;

System::System(int ncells)
{
    particles = 4*ncells*ncells*ncells;
    cells = ncells;
    b = 5.260e-10;
    //cout<<"her"<<endl;
    list = new Particle[particles];
    Initialize();
    cout<<" "<<list[1].gettype()<<list[6].getpos()<< endl;
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
    //integrator = new Integrator_md;
    InitializePositions();
    InitializeVelocities();
}

void System::InitializePositions(){
    double xCoors[] = {0,0.5,0,0.5};
    double yCoors[] = {0,0.5,0.5,0};
    double zCoors[] = {0,0,0.5,0.5};
    vec tmp;
    tmp = zeros<vec>(3);
    int counter = 0;
    for(int x=0; x<cells; x++){
        for(int y=0; y<cells; y++){
            for(int z=0; z<cells; z++){
                for(int k=0; k<3; k++){
                    //cout<<counter<<endl;
                    if(counter<particles){
                        //cout<<"her"<<endl;
                        tmp(0) = b*(x+xCoors[k]); tmp(1) = b*(y+yCoors[k]); tmp(2) = b*(z+zCoors[k]);
                        list[counter].pos = tmp;
                    }
                    counter ++;
                }
            }
        }
    }
}
void System::InitializeVelocities(){
    for(int i=0;i<particles; i++){
        list[i].velocity = (2*randn<vec>(3)-1);
    }
}
void System::output(int nr){
    /*outfile is an ofstram-object letting us open a file
    **u is an armadillo-object containing the solution at time n
    **n is the timestep number
    **scheme is an integer telling what scheme is used to obtain the solution
    **N is the size of the array*/
    ofstream outfile;
    outfile.open("test.xyz");
    outfile<<particles<<endl;
    outfile<<"This is a commentline for comments"<<endl;
    for(int i=0;i<particles;i++){
        outfile<<list[i].gettype()<<" "<<list[i].getpos()<<" "<<list[i].getvel()<<endl;
    }
    outfile.close();
}
void System::update(double dt){
    for(int i=0; i<particles; i++){
        list[i].velocity = list[i].velocity + zeros<vec>(3)*(dt/2*list[i].getmass());
        list[i].pos = list[i].pos +list[i].velocity*dt;
        //update forces???
        list[i].velocity = list[i].velocity + zeros<vec>(3)*(dt/2*list[i].getmass());
    }
}
