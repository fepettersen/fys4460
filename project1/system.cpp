#include "system.h"
using namespace std;
using namespace arma;

System::System(int ncells)
{
    particles = 4*ncells*ncells*ncells;
    cells = ncells;
    b = 5.260/3.405; //Aangstroms
    L = cells*b;
    //cout<<"her"<<endl;
    particle = new Particle[particles];
    Initialize();
    //cout<<" "<<particle[1].gettype()<<particle[6].getpos()<< endl;
}

void System::Initialize()
{
    InitializePositions();
    InitializeVelocities();
}

void System::InitializePositions(){
    double xCoors[] = {0.25,0.75,0.25,0.75};
    double yCoors[] = {0.25,0.75,0.75,0.25};
    double zCoors[] = {0.25,0.25,0.75,0.75};
    vec tmp;
    tmp = zeros<vec>(3);
    int counter = 0;
    for(int x=0; x<cells; x++){
        for(int y=0; y<cells; y++){
            for(int z=0; z<cells; z++){
                for(int k=0; k<4; k++){
                    //cout<<counter<<endl;
                    if(counter<particles){
                        //cout<<"her"<<endl;
                        tmp(0) = b*(x+xCoors[k]); tmp(1) = b*(y+yCoors[k]); tmp(2) = b*(z+zCoors[k]);
                        particle[counter].r = tmp;
                    }
                    counter ++;
                }
            }
        }
    }
}
void System::InitializeVelocities(){
    vec sumvec = zeros<vec>(3);
    for(int i=0;i<particles; i++){
        particle[i].v = randn<vec>(3);
        sumvec += particle[i].v;
    }
    sumvec /=particles;
    for(int i=0;i<particles; i++){
        particle[i].v -=sumvec;
    }
}
void System::output(int nr){
    /*Loops through all particles and writes their positions to a numbered .xyz file*/

    char* buffer = new char[60];
    sprintf(buffer,"results_%03d.xyz",nr);
    ofstream outfile;
    cout<<buffer<<endl;
    outfile.open(buffer);
    outfile<<particles<<endl;
    outfile<<"This is a commentline for comments"<<endl;
    for(int i=0;i<particles;i++){
        outfile<<particle[i].gettype()<<" "<<particle[i].getpos()<<setprecision(12)<<" "<<particle[i].getvel()<<setprecision(12)<<endl;
    }
    outfile.close();
}
void System::update(double dt){
    //vec F;
    for(int i=0; i<particles; i++){
        //F.print("se her");
        particle[i].v = particle[i].v + particle[i].F*(dt/(2.0*particle[i].getmass()));
        particle[i].r = particle[i].r +particle[i].v*dt;
        particle[i].F = grad_U(i);
        if(i==0){
            particle[i].v.print("hastighet!");}
        particle[i].v = particle[i].v + particle[i].F*(dt/(2.0*particle[i].getmass()));
        particle[i].checkpos(L);
    }
}

vec System::force(vec dr){
    //double k_B = 1.38e-23;
    double eps = 1.0; //actually eps/k_B
    double sigma = 1.0;   //Aangstroms
    double r = norm(dr,2);
    vec F = (24*eps*pow(sigma,6)/pow(r,7))*(2*pow((sigma/r),6)-1)*(dr/r);
    return  F;
}

vec System::grad_U(int i){
    vec F = zeros<vec>(3);
    for(int j=0;j<particles;j++){
        if(j!=i){
            F += force(particle[i].distanceToAtom(&particle[j],L));
        }
    }
    return F;
}
