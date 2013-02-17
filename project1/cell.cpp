


#include "project1.h"

using namespace std;
using namespace arma;

Cell::Cell()
{
    cell_no = 0;

    neighbours = new int[26];
    for(int i=0; i<26; i++){
        neighbours[i] = 0;
    }
    pos = zeros(3);
    cellLength = 0;

}
vec3 Cell::distanceToCell(Cell *cell, double L){
      vec3 dr = cell->getPos()-this->pos;
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
int Cell::isincell(Particle *atom, double r_cut){
    int x = 0;
    int y = 0;
    int z = 0;
    vec3 dr = atom->r-pos;
    if(dr[0]<cellLength && dr[0]>0){
        x = 1;
    }
    if(dr[1]<cellLength && dr[1]>0){
        y = 1;
    }
    if(dr[2]<cellLength && dr[2]>0){
        z = 1;
    }
    return (x+y+z)/3;
}
void Cell::addParticle(Particle *atom){
//    cout << particles.capacity() << "  " << particles.size() << "   " << this->getCell_no() << endl;
    particles.push_back(atom);
}
/*
void Cell::FindNeighbours(Cell *cell,double r_cut,double L,int j){
    vec3 dr = zeros(3);
    cout<<"Balle nummer "<<this->cell_no<<" har pos "<<this->pos<<endl;
    int x,y,z;
    x = y = z = 0;
    dr = distanceToCell(cell,L);
    if(dr(0)<=(cellLength+0.033)){
        x=1;
    }
    if(dr(1)<=(cellLength+0.033)){
        y=1;
    }
    if(dr(2)<=(cellLength+0.033)){
        z=1;
    }
    if((x+y+z)/3){
        neighbours[j] = cell->getCell_no();
    }


}
*/
void Cell::FindNeighbours(Cell *cell,double L,int j){
    vec3 dr = cell->getPos()-pos;
    for(int i=0;i<3;i++) {
        if(dr(i) > L/2.0){
            dr(i) -= L;
        }
        else if(dr(i)< -L/2.0){
            dr(i) += L;
        }
    }
    double length = cellLength+0.001;
    int x,y,z;
    x = y = z = 0;
    if(dr(0) <= length){
        x = 1;
    }
    if(dr(1) <= length){
        y = 1;
    }
    if(dr(2) <= length){
        z = 1;
    }
    if((x+y+z)/3 == 1){
        neighbours[j] = cell->getCell_no();
    }
}
