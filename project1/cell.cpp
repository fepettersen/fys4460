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
