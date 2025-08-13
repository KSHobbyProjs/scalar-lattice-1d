#include <iostream>
#include "Field.h"
#include "Metropolis.h"
#include "Simulation.h"

int main() {
    int nx = 32;
    int nt = 32;

    double epsilon = 1.5;
    unsigned seed = 153243;

    int num_thermalize_steps = 50;

    Field phi(nt, nx);
    Metropolis updater(epsilon, seed);
    Simulation sim(phi, updater);
    sim.thermalize(num_thermalize_steps);

    std::cout << "total action: " << phi.total_action() << std::endl;

    return 0;
}
