/**
 * @class Simulation
 * @brief Handles thermalization, sampling, and measurement for a real scalar field on a 2D lattice (time × space).
 *
 * The class needs the field parameters as input (nt, nx, m, lambda, a)
 */

#include "Metropolis.h"
#include "Simulation.h"
#include "Field.h"

#include <fstream>
#include <iostream>
#include <string>

// --------------------------- CONSTRUCTOR ------------------------------
Simulation::Simulation(Field& phi, Metropolis& updater)
    : phi_(phi), updater_(updater) {}

// --------------------------- SAMPLE METHODS ---------------------------
void Simulation::thermalize(int num_therm_steps) {
    // create output file for stats vs sweep steps
    std::ofstream output("output/output.dat");
    if (!output) {
        throw std::runtime_error("Failed to open output/output.dat\n");
    }
    
    // conduct thermalization sweeps, recording <phi2> each sweep
    for (int n = 0; n < num_therm_steps; ++n) { 
        // calculate <phi2> and output to file along with sweep #
        output << n << " " << phi_variance() << "\n";
        updater_.sweep(phi_); 
    }

    // close output file
    output.close();

    // compute the acceptance rate and reset it after printing it
    std::cout << "The acceptance rate is " << updater_.acceptance_rate() << std::endl; 
    updater_.reset_acceptance_rate(); 
}

// --------------------------- MEASUREMENT METHODS ----------------------
double Simulation::phi_variance() const {
    int nx = phi_.length_x();                  ///< field dimensions
    int nt = phi_.length_t();                  ///< slightly less efficient than declaring them at the topo once,
                                               ///  but alternative is not a clean separation of concerns (couples Field and Sim too much)
    double phi_variance = 0;
    for (int t = 0; t < nt; ++t) {
        for (int x = 0; x < nx; ++x){
            double phi = phi_(t, x);
            phi_variance += phi * phi;
        }
    }
    phi_variance /= (nt * nx);
    return phi_variance;
}
