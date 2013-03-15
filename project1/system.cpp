
#include "project1.h"

using namespace std;
using namespace arma;


/* Initializers*/
System::System(int ncells, int Timesteps, double Temperature)
{
//    bool StartFromInput = true;
//    bool rescale = true;
//    double factor = 2.0;
    timesteps = Timesteps;
    T = Temperature;
    particles = 4*ncells*ncells*ncells;
    b = 5.72/3.405; //Aangstroms 5.260
    L = ncells*b;
    r_cut = 3;
    Ncells = ncells;

//    if(StartFromInput){
//        ifstream infile ("Setup.xyz");
//        string line;
//        getline(infile,line);
//        particles =  atoi(line.c_str());
//    }
//    if(rescale){
//        L*=factor;
//    }
    xcells = L/r_cut;
    cells = xcells*xcells*xcells;
    particle = new Particle[particles];
    U = 0;
    pressure = 0;
    potential = 0;
    res = zeros<mat>(timesteps+1,2);

    for(int i = 0; i < cells; i++) {
        cell.push_back(new Cell());
    }
    Initialize();
}

void System::Initialize()
{
    cout<<"Initializing "<<particles<<" particles placed in "<<cells<<" cells......";
    InitializePositions();
    InitializeVelocities(T);
    setupCells();

    /*Calculate forces for the first timestep*/
    int n;

#pragma omp parallel
    {
        double U_thread = 0;
        double p_thread = 0;

#pragma omp for// private(p_thread,U_thread)
    for(int j=0; j<cells;j++){
        for(vector<Particle*>::iterator it1 = cell[j]->particles.begin(); it1 != cell[j]->particles.end(); it1++){
            (*it1)->F = grad_U_new(cell[j],*it1,U_thread, p_thread);
            for(int k=0; k<cell[j]->number_of_neighbours;k++){
                n = cell[j]->neighbours[k];
                (*it1)->F += grad_U_new(cell[n],*it1,U_thread,p_thread);
            }
        }
    }
#pragma omp critical
    {
    pressure += p_thread;
    potential += U_thread;
    }
    }
    cout<<"done"<<endl;
}

void System::InitializePositions(){
    /*Gices each atom a position in an FCC lattice*/
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
                        particle[counter].sysIndex = counter;
                        particle[counter].r_tmp = tmp;
                        particle[counter].r0 = tmp;
                    }
                    counter ++;
                }
            }
        }
    }
}

void System::InitializeVelocities(double T){
    /*Gives each particle a random velocity*/
    vec3 sumvec = zeros(3);
    for(int i=0;i<particles; i++){
//        particle[i].v = sqrt(T)*randn<vec>(3);
        particle[i].v = sqrt(T)*randu<vec>(3);
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
                for(int b=0;b<3;b++){
                    cell[counter]->pos2(b) = fmod(tmp(b),len);
                }
                counter++;
            }
        }
    }
    vec3 dr = zeros(3);
    vec3 r1 = zeros(3);
    vec3 r2 = zeros(3);
    double length = L/((double) xcells)+0.001;
    double limit = sqrt(3)*L/((double) xcells)+0.001;
    int dummy;

    /*Find neighbour cells*/
    for(int i=0; i<cells;i++){
        r1 = cell[i]->getPos();
        dummy = 0;
        for(int j=0; j<i;j++){
            r2 = cell[j]->getPos();
            dr = r2-r1;
            for(int k=0;k<3;k++) {
                if(dr(k) > L/2.0){
                    dr(k) -= L;
                }
                else if(dr(k)< -L/2.0){
                    dr(k) += L;
                }
            }

            length = norm(dr,2);
            if(length <=limit){
                cell[i]->neighbours[dummy] = cell[j]->getCell_no();
                dummy++;
            }
        }
        for(int j=i+1; j<cells;j++){
            r2 = cell[j]->getPos();
            dr = r2-r1;
            for(int l=0;l<3;l++) {
                if(dr(l) > L/2.0){
                    dr(l) -= L;
                }
                else if(dr(l)< -L/2.0){
                    dr(l) += L;
                }
            }

            length = norm(dr,2);
            if(length <=limit){
                cell[i]->neighbours[dummy] = cell[j]->getCell_no();
                dummy++;
            }
        }
    }

    /*Place particles in cells*/

    for(int i=0; i<cells;i++){
        for(int j=0; j<particles; j++){
            if(cell[i]->isincell(&particle[j])){
                particle[j].cellID = cell[i]->getCell_no();
                cell[i]->addParticle(&particle[j]);
            }
        }
    }
}

/*Updaters*/

//void System::update(double dt){
//    /*The brute force function - no cells*/
//    for(int i=0; i<particles; i++){
//        particle[i].v = particle[i].v + particle[i].F*(dt/2.0);
//        particle[i].r_tmp = particle[i].r +particle[i].v*dt;

//        if(i==0){
//            cout << particle[i].F << endl;
//        }
//    }
//    accept();
//    for(int i=0;i<particles;i++){
//        particle[i].F = grad_U(i);
//        particle[i].v = particle[i].v + particle[i].F*(dt/2.0);

//    }
//}

void System::update_all(double dt){
    /*The update function using cells and neighbours*/
    U = 0;
    pressure = 0;
    potential = 0;
    string type = "Ar";

#pragma omp parallel for
    for(int a=0;a<cells;a++){
        for(vector<Particle*>::iterator it1 = cell[a]->particles.begin(); it1 != cell[a]->particles.end(); it1++){
            /*SRSLY you guys, I hate you guys so much!*/
            /*Legg en god forklaring paa dette et setd!*/
            if((*it1)->gettype()==type){
                (*it1)->v = (*it1)->v + (*it1)->F*(dt/2.0);
                (*it1)->r_tmp = (*it1)->r + (*it1)->v*dt;
                (*it1)->delta_r += distance((*it1)->r_tmp,(*it1)->r);   //Calculate total displacement from initial pos
            }
        }
    }
    accept();
    PlaceInCells();
    /*Calculates the forces*/
    mat forces = zeros(3,particles);
#pragma omp parallel
    {
        vector<Particle*>::iterator it1 ;
        int n = 0;
        double U_thread = 0;
        double p_thread = 0;
        mat thread_forces = zeros(3,particles);
#pragma omp for schedule(static,4)
        for(int j=0; j<cells;j++){
//            cout<<"j = "<<j<<endl;
            for(it1 = cell[j]->particles.begin(); it1 != cell[j]->particles.end(); it1++){
//                thread_forces.col((*it1)->sysIndex) += grad_U_new(cell[j], *it1, U_thread, p_thread);
                if((*it1)->gettype() == type){
                    (*it1)->F = grad_U_new(cell[j],*it1,U_thread, p_thread);
                    for(int k=0; k<cell[j]->number_of_neighbours;k++){
                        n = cell[j]->neighbours[k];
//                        thread_forces.col((*it1)->sysIndex) += grad_U_new(cell[n],*it1,U_thread,p_thread);
                        (*it1)->F += grad_U_new(cell[n],*it1,U_thread,p_thread);
                    }
                    (*it1)->v = (*it1)->v + (*it1)->F*(dt/2.0);
                }
            }
        }
#pragma omp critical
        {
            forces += thread_forces;
            potential +=  U_thread;
            pressure += p_thread;
            //            cout<<"potential "<<U_thread<<" total "<<potential<<endl;
        }
    }
//    for(int i=0;i<particles;i++){
//        particle[i].F = forces.col(particle[i].sysIndex);
//        particle[i].v = particle[i].v + particle[i].F*(dt/2.0);
//    }

}

void System::accept(){
    /*updates the positions off all atoms*/
    for(int i=0; i<particles;i++){
        particle[i].r = particle[i].r_tmp;
        particle[i].checkpos(L);
    }
}

void System::PlaceInCells(){
    /*Removes all atoms from cells and places new ones*/
    for(int i=0; i<cells;i++){
        cell[i]->particles.clear();
        for(int j=0; j<particles; j++){
            if(cell[i]->isincell(&particle[j])){
                cell[i]->addParticle(&particle[j]);
            }
        }
    }
}

void System::mean_square(int nr){
    /*calculates total displacement*/
    for(int i=0; i<particles; i++){
        U += dot(particle[i].delta_r,particle[i].delta_r);

    }
    res(nr,0)=U;
    res(nr,1)=pressure/2.0;
}

void System::BerendsenThermostat(){
    /*rescales the velocities aff all atoms*/
    double tau = 1.0/10;
    double E_k = 0;
    for(int i=0; i<particles;i++){
        E_k += 0.5*dot(particle[i].v,particle[i].v);
    }
    double temp = 2*E_k/(3.0*particles);
    double gamma = sqrt(1 + tau*((T/temp)-1));
    for(int i=0; i<particles;i++){
        particle[i].v *= gamma;
    }
}

void System::AndersenThermostat(double dt){
    /*rescales the velocities aff all atoms*/
    double tau = dt/10;
    double T_bath = sqrt(T);
    vec random_number = randu<vec>(particles);
    for(int i=0; i<particles;i++){
        if(tau<random_number(i)){
            particle[i].v = T_bath*randn<vec>(3);
        }
    }
}

void System::Cylinder(double radius){
    double R = radius/3.405;
    string newtype = "Stargon";
    double r = 0;
    double rx = 0;
    double ry = 0;
    for(int i = 0; i<particles; i++){
        rx = L/2.0 - particle[i].r(0);
        ry = L/2.0 - particle[i].r(1);
        r = sqrt(rx*rx+ry*ry);
        if(fabs(r)>R){
            particle[i].settype(newtype);
        }
    }
    ofstream new_outfile;
    new_outfile.open("Setup.xyz");
    new_outfile<<particles<<endl;
    new_outfile<<"Commentline for comments"<<endl;
    for(int i=0; i<particles; i++) {
        new_outfile<<particle[i].gettype()<<" "<<particle[i].getpos()<<" "<<particle[i].getvel()
              <<" "<<particle[i].cellID<<"  "<<particle[i].getForce()<<"  "<<endl;
    }
    new_outfile.close();
}

void System::Spheres(int numSpheres, double rmin, double rmax){
    rmin /= 3.405;
    rmax /= 3.405;
    string newtype = "Stargon";
    string oldtype = particle[0].gettype();
    for(int n=0;n<particles;n++)
        particle[n].settype(newtype);

    mat positions = rmin + (L-rmin)*randu<mat>(3,numSpheres);
    vec radii = rmin + (rmax-rmin)*randu<vec>(numSpheres);
    positions.print("positions");
    radii.print("radii");
    double r, rx,ry,rz;
    for(int j = 0; j<numSpheres;j++){
        for(int i=0; i<particles;i++){
            rx = positions(0,j) - particle[i].r(0);
            ry = positions(1,j) - particle[i].r(1);
            rz = positions(2,j) - particle[i].r(2);
            r = sqrt(rx*rx + ry*ry + rz*rz);
            if(r < radii[j]){
                particle[i].settype(oldtype);
            }
        }
    }
    ofstream new_outfile;
    new_outfile.open("Setup.xyz");
    new_outfile<<particles<<endl;
    new_outfile<<"Commentline for comments"<<endl;
    for(int i=0; i<particles; i++) {
        new_outfile<<particle[i].gettype()<<" "<<particle[i].getpos()<<" "<<particle[i].getvel()
              <<" "<<particle[i].cellID<<"  "<<particle[i].getForce()<<"  "<<endl;
    }
    new_outfile.close();
}

/*Helper functions*/

vec3 System::force(vec dr,double &U_thread, double &p_thread){
    /*Calculates single-pair forces*/
//    if (norm(dr)>r_cut){
//        return zeros(3);
//    }
    double r2 = dot(dr,dr);
    double r6 = r2*r2*r2;
    double r12 = r6*r6;
    vec3 F = 24*(2.0/r12 -1.0/r6)*(dr/r2);
    p_thread += dot(F,dr);
    U_thread += 4*(1.0/r12-1.0/r6);
    return  F;
}

//vec3 System::grad_U(int i){
//    /*from brute force version. caculates sum F on a particle*/
//    vec3 F = zeros(3);
//    for(int j=0;j<i;j++){
//        F += force(particle[i].distanceToAtom(&particle[j],L));
//    }
//    for(int j=i+1;j<particles;j++){
//        F += force(particle[i].distanceToAtom(&particle[j],L));
//    }
//    return -F;
//}

vec3 System::grad_U_new(Cell *box,Particle *thisParticle,double &U_thread,double &p_thread){
    /*calculates sum F on an atom from all atoms in a cell*/
    vec3 F = zeros(3);
    for(vector<Particle*>::iterator it2 = box->particles.begin(); it2 != box->particles.end(); it2++){
        if(*it2 != thisParticle){
            F += force(thisParticle->distanceToAtom(*it2,L),U_thread,p_thread);
        }
    }
    return -F;
}

vec3 System::distance(vec3 r_new, vec3 r_old){
    /*for displacement calculation*/
    vec3 dr = r_new-r_old;
    for(int i=0;i<3;i++) {
        if(dr(i) > L/2.0){
            dr(i) -= L;
        }
        else if(dr(i)< -L/2.0){
            dr(i) += L;
        }
    }
    return dr;
}


/*Output*/

void System::outputMeanSquare(){
    char* buffer = new char[60];
    sprintf(buffer,"total_movement_.txt");
    ofstream outfile;
    outfile.open(buffer);
    for(int i=0;i<=timesteps;i++){
        outfile<<res(i,0)<<setprecision(12)<<"  "<<res(i,1)<<setprecision(12)<<endl;
    }
    outfile.close();
}

void System::output(int nr){
    /*Loops through all particles and writes their positions to a numbered .xyz file*/

    char* buffer = new char[60];
//    sprintf(buffer,"results_%04d.xyz",nr);
    sprintf(buffer,"results_%04d.bin",nr);
    ofstream outfile;
//    cout<<buffer<<endl;
    outfile.open(buffer,ios::binary);
    outfile<<particles<<endl;
    outfile<<"Argon atoms using Lennard - Jones potential. timestep "<<nr<<"  "<<potential<<setprecision(12)<<endl;
    for(int i=0;i<particles;i++){
        outfile<<particle[i].gettype()<<" "<<particle[i].getpos()<<" "<<particle[i].getvel()
              <<" "<<particle[i].cellID<<"  "<<particle[i].getForce()<<"  "<<endl;
    }
      outfile.close();
}

void System::Input(){
    cout<<"Importing nanoporous matrix...";
    string line;
    ifstream infile ("Setup.xyz");
    getline(infile,line);
    int nparticles = atoi(line.c_str());
    vec tmp = zeros<vec>(10);
    int celltmp = -1;
    int counter,k;
    getline(infile,line);
    string type;

    for(int n=0;n<nparticles;n++){   //while(infile.good())
        getline(infile,line);
        istringstream iss(line);
        counter = 0;
        k = 0;
        do
        {
            string sub;
            iss >> sub;
            if(counter ==0){
                type = sub;
            }
            else if(counter == 7){
                celltmp = atoi(sub.c_str());
            }
            else {
                tmp(k) = atof(sub.c_str());
                k++;
            }
            counter ++;
        } while (iss);
        particle[n].settype(type);
        particle[n].cellID = celltmp;
        for(int t=0; t<3;t++){
            particle[n].r(t) = tmp(t);
            particle[n].v(t) = tmp(t+3);
            particle[n].F(t) = tmp(t+6);
        }
    }
    cout<<" done!"<<endl;
    infile.close();
}

void System::AdjustDensity(double factor){


    cout<<"Reducing density of fluid by factor of "<<factor<<" ...";
    int nArgon = 0;
    string emil = "Ar";

    for(int i = 0; i<particles;i++){
        if(particle[i].gettype() == emil){
            nArgon ++;
        }
    }

    int new_particles = particles - ((int) nArgon/factor);
    Particle *old_particle, *argon;
    old_particle = new Particle[particles];
    argon = new Particle[nArgon];

    for(int i = 0; i<particles;i++){
        old_particle[i] = particle[i];
    }

    particle = new Particle[new_particles];
    int counter = 0;
    int dummy = 0;

    for(int i = 0; i<particles;i++){
        if(old_particle[i].gettype() != emil){
            particle[counter] = old_particle[i];
            counter ++;
        }
        else if(old_particle[i].gettype() == emil && i%2 ==0){
            argon[dummy] = old_particle[i];
            dummy++;
        }
    }
//    cout<<counter<<endl;
    dummy = 0;
    while(counter <  new_particles){
        particle[counter] = argon[dummy];
        counter ++;
        dummy ++;
    }
    particles = new_particles;
    cout<<"great sucsess! The system now consists of "<<dummy<<" Ar atoms as opposed to "<<nArgon<<endl;

    ofstream new_outfile;
    new_outfile.open("Setup_test.xyz");
    new_outfile<<particles<<endl;
    new_outfile<<"Commentline for comments"<<endl;
    for(int i=0; i<particles; i++) {
        new_outfile<<particle[i].gettype()<<" "<<particle[i].getpos()<<" "<<particle[i].getvel()
              <<" "<<particle[i].cellID<<"  "<<particle[i].getForce()<<"  "<<endl;
    }
    new_outfile.close();
}
