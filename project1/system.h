
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
    void Initialize();
    void InitializePositions();
    void InitializeVelocities(double T);
    void output(int nr);
    arma::vec3 grad_U(int i);
    void accept();
    void setupCells();
    void update_all(double dt, bool drive);
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
    void Thermalize(int steps, double dt, bool makespheres, bool ToScreen);
    void timeRemaining(double timediff,int totaltimesteps, int completedsteps, int elapsed, char *buffer);
    double timediff(double time1, double time2);
    void SimulateFlow(double dt, bool ToScreen);
    arma::vec3 distance(arma::vec3 r_new, arma::vec3 r_old);
    void PrintVelocity();

    /*values*/
    arma::mat res;
    Particle *particle;
    std::vector<Cell*> cell;
    double r_cut;
    std::string type;
private:
    /*Methods*/
    arma::vec3 force(arma::vec3, double &U_thread, double &p_thread);

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
