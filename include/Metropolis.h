// Metropolis.h
// Header for a class that handles Metropolis updates
// epsilon is the step for the proposed change distro eta = [-epsilon, epsilon]
// seed is the seed for the PRNG

#pragma once
#include "Field.h"
#include <random>

class Metropolis {
    public:
        // ------------------ CONSTRUCTOR -----------------
        Metropolis(Field& phi, double epsilon, unsigned seed = 10531);

        // ------------------ ACCESSORS --------------------
        const Field& phi() const {return phi_;}

        // ------------------ UPDATE METHODS ---------------
        void sweep();                                                 ///< sweeps over all lattice points

    private:
        Field& phi_;                                                  ///< field data reference
        std::mt19937 rng_;                                            ///< PRNG (Mersenne Twister)
        std::uniform_real_distribution<double> proposed_change_dist_; ///< uniform distribution for proposed change eta 
        std::uniform_real_distribution<double> accept_dist_;          ///< uniform distribution for accept / reject prob

        // ------------------ UPDATE METHODS ---------------
        double propose_change();                                      ///< alters a field value at a lattice point
        bool accept_reject(double delta_s);                           ///< decides to keep or reject a change based on dS
};
