


#include "project2.h"

using namespace std;
using namespace arma;

Cell::Cell()
{
    cell_no = 0;
    number_of_neighbours = 26;
    neighbours = new int[number_of_neighbours];
    for(int i=0; i<number_of_neighbours; i++){
        neighbours[i] = 0;
    }
    pos = zeros(3);
    pos2 = zeros(3);
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
int Cell::isincell(Particle *atom){
    /*checks if an atom is in the cell*/
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
    /*adds an atom to a cell*/
    particles.push_back(atom);
}

void Cell::FindNeighbours(Cell *cell,double L,int j){
    /*I dont think I am using this... dont think it works*/
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
