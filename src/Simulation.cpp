/**
 * @class Simulation
 * @brief Handles thermalization, sampling, and measurement for a real scalar field on a 2D lattice (time × space).
 *
 * The class needs the field parameters as input (nt, nx, m, lambda, a)
 */

#include "Metropolis.h"
#include "Simulation.h"
#include "Field.h"

// --------------------------- CONSTRUCTOR ------------------------------
Simulation::Simulation(Metropolis& updater)
    : updater_(updater) {}

// --------------------------- SAMPLE METHODS ---------------------------
void Simulation::thermalize(int num_therm_steps) {
    for (int _ = 0; _ < num_therm_steps; ++_){ updater_.sweep(); }
}

// --------------------------- MEASUREMENT METHODS ----------------------
double Simulation::phi_spatial_avg() const {
    const Field& phi = updater_.phi();
    return 0;
}
