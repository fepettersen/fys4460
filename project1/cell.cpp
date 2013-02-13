#include "cell.h"
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

    particles = new vector<Particle*>;
}
vec3 Cell::distanceToCell(Cell *cell, double L){
      vec3 dr = cell->getPos()-pos;
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
    if(dr[0]<r_cut && dr[0]>0){
        x = 1;
    }
    if(dr[1]<r_cut && dr[1]>0){
        y = 1;
    }
    if(dr[2]<r_cut && dr[2]>0){
        z = 1;
    }
    return (x+y+z)/3;
}
void Cell::addParticle(Particle *atom){
    particles.push_back(&atom);
}
