// Simulation.h
// A header for a class that handles simulation of an nt x nx lattice with periodic BCs
// Supports thermalization of field with varying step parameter, sampling of fields, and
// measurement of <phi^2> and other correlators

#pragma once
#include "Metropolis.h"

class Simulation {
    public:
        // ---------------------- CONSTRUCTOR -----------------------
        Simulation(Field& phi, Metropolis& updater);
   
        // ---------------------- SAMPLING METHODS ------------------
        void thermalize(int num_therm_steps);
        void sample(int num_samples, int num_sweeps);

        // ---------------------- MEASUREMENT METHODS ---------------
        double phi_spatial_avg() const;

    private:
        Metropolis& updater_;         ///< metropolis update class
        Field& phi_;                  ///< reference to the field object
};
