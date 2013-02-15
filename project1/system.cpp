#include "system.h"
using namespace std;
using namespace arma;

System::System(int ncells)
{
    particles = 4*ncells*ncells*ncells;
    b = 5.260/3.405; //Aangstroms
    L = ncells*b;
    r_cut = 3;
    cells = 27;//L/r_cut;
    particle = new Particle[particles];
    cell = new Cell[cells];
    Initialize();
    //cout<<" "<<particle[1].gettype()<<particle[6].getpos()<< endl;
}

void System::Initialize()
{
    InitializePositions();
    InitializeVelocities();
    setupCells();
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
                        particle[counter].r_tmp = tmp;
                    }
                    counter ++;
                }
            }
        }
    }
}
void System::InitializeVelocities(){
    vec3 sumvec = zeros(3); new Cell[cells];
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
        particle[i].v = particle[i].v + particle[i].F*(dt/2.0);
        particle[i].r_tmp = particle[i].r +particle[i].v*dt;

        if(i==0){
            cout << particle[i].F << endl;
        }
    }
    accept();
    for(int i=0;i<particles;i++){
        particle[i].F = grad_U(i);
        particle[i].v = particle[i].v + particle[i].F*(dt/2.0);

    }
}
void System::update_all(double dt){
    //This will eventually be the update function utilizing neighbour lists
    int index = 0;
    int n = 0;
//    Particle atom;
    for(int a=0;a<cells;a++){
        for(list<Particle*>::iterator it1 = cell[a].particles.begin(); it1 != cell[a].particles.end(); it1++){
            /*SRSLY you guys, I hate you guys so much!*/
            /*Legg en god forklaring paa dette et setd!*/
            (*it1)->v = (*it1)->v + (*it1)->F*(dt/2.0);
            (*it1)->r_tmp = (*it1)->r + (*it1)->v*dt;
        }
    }
//    move particles within cells
    accept();
    for(int j=0; j<cells;j++){
        index = 0;
        for(list<Particle*>::iterator it1 = cell[j].particles.begin(); it1 != cell[j].particles.end(); it1++){
            (*it1)->F = grad_U_new(&cell[j],index,*it1);
            index++;
            for(int k=0; k<26;k++){
                n = cell[j].neighbours[k];
                for(list<Particle*>::iterator it2 = cell[n].particles.begin(); it2 != cell[n].particles.end(); it2++){
                    (*it1)->F -= force((*it1)->distanceToAtom(*it2,L));
                }
            }
            (*it1)->v = (*it1)->v + (*it1)->F*(dt/2.0);
        }
    }
}

vec System::force(vec dr){
    //double k_B = 1.38e-23;
    //double eps = 1.0; //actually eps/k_B
    //double sigma = 1.0;   //Aangstroms
    double r2 = dot(dr,dr);
    double r6 = r2*r2*r2;
    double r12 = r6*r6;
    //vec F = (24*eps*pow(sigma,6)/pow(r,7))*(2*pow((sigma/r),6)-1)*(dr/r);
    vec F = 24*(2.0/r12 -1.0/r6)*(dr/r2);
    return  F;
}
/*
vec3 System::newForce(vec3 dr){
    if (norm(dr)>r_cut){
        return zeros(3);
    }
    double r2 = dot(dr,dr);
    double r6 = r2*r2*r2;
    double r12 = r6*r6;
    vec F = 24*(2.0/r12 -1.0/r6)*(dr/r2);
    return  F;
}
*/
vec3 System::grad_U(int i){
    vec3 F = zeros(3);
    for(int j=0;j<i;j++){
        F += force(particle[i].distanceToAtom(&particle[j],L));
    }
    for(int j=i+1;j<particles;j++){
        F += force(particle[i].distanceToAtom(&particle[j],L));
    }
    return -F;
}
vec3 System::grad_U_new(Cell *box,int thisIndex, Particle *thisParticle){
    //løp over partiklene i en celle
    vec3 F = zeros(3);
//    int thisIndex = 0;
    for(list<Particle*>::iterator it2 = box->particles.begin(); it2 != box->particles.end(); it2++){
        if(thisIndex==(distance(box->particles.begin(),it2))){
            advance(*it2,1);
        }

        F += force(thisParticle->distanceToAtom(*it2,L));
//        thisIndex++;
    }
    return -F;
}
void System::accept(){
    for(int i=0; i<particles;i++){
        particle[i].r = particle[i].r_tmp;
        particle[i].checkpos(L);
    }
}
/*
void System::acceptInCell(){
    for(int i=0; i<particles;i++){
        particle[i].r = particle[i].r_tmp;
        particle[i].checkpos(L);
    }
}
*/
void System::setupCells(){

    /*Give cellnumbers*/
    for(int i=0;i<cells;i++){
        cell[i].setCell_no(i);
    }
    int xcells,ycells,zcells;
    xcells=ycells=zcells= 3;    //should be set another place

    /*Give cells positions*/
    vec3 tmp;
    tmp = zeros(3);
    int counter = 0;
    for(int x=0; x<xcells; x++){
        for(int y=0; y<ycells; y++){
            for(int z=0; z<zcells; z++){
                tmp(0) = x*r_cut; tmp(1) = y*r_cut; tmp(2) = z*r_cut;
                cell[counter].setPos(tmp);
                counter++;
            }
        }
    }

    /*Find neighbours*/
    for(int i=0; i<cells;i++){
        for(int j=0; j<i;j++){
            cell[i].FindNeighbours(&cell[j],r_cut,L,j);
        }
        for(int j=i+1; j<cells;j++){
            cell[i].FindNeighbours(&cell[j],r_cut,L,j-1);
        }
    }

    /*Place particles in cells*/
    for(int i=0; i<cells;i++){
        for(int j=0; j<particles; j++){
            if(cell[i].isincell(&particle[j],r_cut)){
                cell[i].addParticle(&particle[j]);
            }
        }
    }
//    cout<<"cell[3].particle: "<<cell[7].particles(3)'' <<endl;
}
