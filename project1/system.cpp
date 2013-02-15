
#include "project1.h"

using namespace std;
using namespace arma;

System::System(int ncells)
{
    particles = 4*ncells*ncells*ncells;
    b = 5.260/3.405; //Aangstroms
    L = ncells*b;
    r_cut = 3;
    Ncells = ncells;
    xcells = L/r_cut;
    cells = xcells*xcells*xcells;
    particle = new Particle[particles];
//    cell = new Cell*[cells];
    for(int i = 0; i < cells; i++) {
        cell.push_back(new Cell());
    }
    Initialize();
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
    for(int x=0; x<Ncells; x++){
        for(int y=0; y<Ncells; y++){
            for(int z=0; z<Ncells; z++){
                for(int k=0; k<4; k++){
                    if(counter<particles){
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
    vec3 sumvec = zeros(3);
    for(int i=0;i<particles; i++){
        particle[i].v = randn<vec>(3);
        sumvec += particle[i].v;
    }
    sumvec /=particles;
    for(int i=0;i<particles; i++){
        particle[i].v -=sumvec;
    }
}
void System::setupCells(){

    /*Give cellnumbers*/
    for(int i=0;i<cells;i++){
        Cell* celli = cell[i];
        cell[i]->setCell_no(i);
        cell[i]->setLenght(L/((double) xcells));
    }

    /*Give cells positions*/
    vec3 tmp;
    tmp = zeros(3);
    double len = cell[0]->getLength();

    int counter = 0;
    for(int x=0; x<xcells; x++){
        for(int y=0; y<xcells; y++){
            for(int z=0; z<xcells; z++){
                tmp(0) = x*len; tmp(1) = y*len; tmp(2) = z*len;
                cell.at(counter)->setPos(tmp);
                counter++;
            }
        }
    }

    /*Find neighbours*/
    for(int i=0; i<cells;i++){
        cout<<i<<endl;
        for(int j=0; j<i;j++){
            cell.at(i)->FindNeighbours(cell.at(j),r_cut,L,j);
        }
        for(int j=i+1; j<cells;j++){
            cell.at(i)->FindNeighbours(cell.at(j),r_cut,L,j-1);
        }
    }

    /*Place particles in cells*/

    for(int i=0; i<cells;i++){
        cout<<"balle "<<i<<endl;
        for(int j=0; j<particles; j++){
            if(cell[i]->isincell(&particle[j],r_cut)){
                particle[j].cellID = cell[i]->getCell_no();
                cell[i]->addParticle(&particle[j]);
            }
        }
    }
}
void System::output(int nr){
    /*Loops through all particles and writes their positions to a numbered .xyz file*/

    char* buffer = new char[60];
    sprintf(buffer,"results_%03d.xyz",nr);
    ofstream outfile;
    cout<<buffer<<endl;

//    cout<<particles<<endl;
    outfile.open(buffer);

    outfile<<particles<<endl;
//    cout<<"This is a commentline for comments"<<endl;

    outfile<<"This is a commentline for comments"<<endl;
    for(int i=0;i<particles;i++){
//        cout << i << endl;
        outfile<<particle[i].gettype()<<" "<<particle[i].getpos()<<setprecision(12)<<" "<<particle[i].getvel()<<setprecision(12)
              <<" "<<particle[i].cellID<<endl;
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
        for(vector<Particle*>::iterator it1 = cell[a]->particles.begin(); it1 != cell[a]->particles.end(); it1++){
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
        for(vector<Particle*>::iterator it1 = cell[j]->particles.begin(); it1 != cell[j]->particles.end(); it1++){
            (*it1)->F = grad_U_new(cell[j],index,*it1);
            index++;
            for(int k=0; k<26;k++){
                n = cell[j]->neighbours[k];
                for(vector<Particle*>::iterator it2 = cell[n]->particles.begin(); it2 != cell[n]->particles.end(); it2++){
                    (*it1)->F -= force((*it1)->distanceToAtom(*it2,L));
                }
            }
            (*it1)->v = (*it1)->v + (*it1)->F*(dt/2.0);
        }
    }
}

vec System::force(vec dr){
//    if (norm(dr)>r_cut){
//        return zeros(3);
//    }
    double r2 = dot(dr,dr);
    double r6 = r2*r2*r2;
    double r12 = r6*r6;
    //vec F = (24*eps*pow(sigma,6)/pow(r,7))*(2*pow((sigma/r),6)-1)*(dr/r);
    vec F = 24*(2.0/r12 -1.0/r6)*(dr/r2);
    return  F;
}

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
    for(vector<Particle*>::iterator it2 = box->particles.begin(); it2 != box->particles.end(); it2++){
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


