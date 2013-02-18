#ifndef CELL_H
#define CELL_H

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
    int isincell(Particle *atom);
    void addParticle(Particle *atom);
    void FindNeighbours(Cell *cell, double L, int j);
    void setLenght(double length){cellLength = length;}
    double getLength(){return cellLength;}

    /*values*/
    int *neighbours;
    std::vector<Particle*> particles;
    arma::vec3 pos2;

private:
    /*Methods*/

    /*values*/
    int cell_no;
    double cellLength;
    arma::vec3 pos;

};

#endif // CELL_H
