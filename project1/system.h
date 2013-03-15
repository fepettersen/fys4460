
#ifndef SYSTEM_H
#define SYSTEM_H
/*
  The system object updates and keeps track of the cells and the particles.
  Though it has a lot of values, theese are mostly service values. The system
  constructor takes in an int value ncells which is NOT the number of cells
  (the number of cells is calculated from r_cut which is the cutoff lenght).
  The number of particles in the system is 4*pow(ncells,3).
  */
class System
{
public:
    /*Methods*/
    System(int ncells, int Timesteps,double Temperature);
    int getParticles(){return particles;}
    void setBalle(int newParticles){particles = newParticles;}
    void Initialize();
    void InitializePositions();
    void InitializeVelocities(double T);
    void output(int nr);
    void update(double dt);
    void boundary_pos();
    arma::vec3 grad_U(int i);
    void accept();
    void setupCells();
    void update_all(double dt);
    arma::vec3 grad_U_new(Cell *box, Particle *thisParticle, double &U_thread, double &p_thread);
    void PlaceInCells();
    void mean_square(int nr);
    void outputMeanSquare();
    void BerendsenThermostat();
    void AndersenThermostat(double dt);
    void Cylinder(double radius);
    void Spheres(int numSpheres, double rmin, double rmax);
    void Input();
    void AdjustDensity(double factor);

    arma::vec3 distance(arma::vec3 r_new, arma::vec3 r_old);
    arma::mat res;
    /*values*/
    Particle *particle;
    std::vector<Cell*> cell;
    double r_cut;
private:
    /*Methods*/
    arma::vec3 force(arma::vec dr, double &U_thread, double &p_thread);

    /*values*/
    int particles;
    int cells;
    int Ncells;
    int xcells;
    double b;   //lattice constant
    double L;
    double U;
    double potential;
    double pressure;
    int timesteps;
    double T;
};

#endif // BALLE_H
