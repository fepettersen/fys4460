#include <iostream>
#include <project1.h>
#include "particle.h"
using namespace std;

int main()
{
    Particle *printballe = new Particle("balle");
     cout << printballe->gettype() << endl;
    printballe->settype("hesteballe");
    cout << "Hello World!" << printballe->gettype() << endl;
    return 0;
}

