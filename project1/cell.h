#ifndef CELL_H
#define CELL_H
#include "project1.h"
#include "particle.h"
#include <vector>
//#include <armadillo>

class Cell
{
public:
    /*Methods*/
    Cell();
    int getCell_no(){return cell_no;}
    void setCell_no(int newCell_no){cell_no = newCell_no;}
    arma::vec3 getPos(){return pos;}
    void setPos(arma::vec3 Newpos){pos = Newpos;}
    arma::vec3 distanceToCell(Cell *cell,double L);
    int isincell(Particle *atom,double r_cut);
    void addParticle(Particle *atom);
    /*values*/
    int *neighbours;
    std::vector<Particle*> particles;
private:
    /*Methods*/

    /*values*/
    int cell_no;
    arma::vec3 pos;

};

#endif // INTEGRATOR_MD_H
