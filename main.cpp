#include <iostream>
#include "Field.h"
#include "Metropolis.h"
#include "Simulation.h"

int main() {
    int nx = 32;
    int nt = 32;

    double epsilon = 1.0;
    unsigned seed = 153243;
    
    Field phi(nt, nx);
    Metropolis updater(epsilon, seed);
    Simulation sim(phi, updater);
    
    std::cout << "phi(2,2) from 1.0 to 0.0 " << phi.local_action_change(2, 2, 1.0) << std::endl;
    // phi(2,3) = 42.0; // set a value
    std::cout << "phi(5,0) = " << phi(5,0) << std::endl;
    
    std::cout << "Length in x: " << phi.length_x() << std::endl;
    std::cout << "Length in t: " << phi.length_t() << std::endl;
    std::cout << "mass: " << phi.mass() << std::endl;
    std::cout << "lambda: " << phi.lambda() << std::endl;

    std::cout << "total action: " << phi.total_action() << std::endl;

    return 0;
}
