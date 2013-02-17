
#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
public:
    /*Methods*/
    System(int ncells);
    int getParticles(){return particles;}
    void setBalle(int newParticles){particles = newParticles;}
    void Initialize();
    void InitializePositions();
    void InitializeVelocities();
    void output(int nr);
    void update(double dt);
    void boundary_pos();
    arma::vec3 grad_U(int i);
    void accept();
    void setupCells();
    void update_all(double dt);
    arma::vec3 grad_U_new(Cell *box, int thisIndex, Particle *thisParticle);
    void PlaceInCells();

    /*values*/
    Particle *particle;
    std::vector<Cell*> cell;
    double r_cut;
private:
    /*Methods*/
    arma::vec3 force(arma::vec dr);

    /*values*/
    int particles;
    int cells;
    int Ncells;
    int xcells;
    double b;   //lattice constant
    double L;
};

#endif // BALLE_H
