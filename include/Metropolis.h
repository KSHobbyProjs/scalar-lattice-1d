// Metropolis.h
// Header for a class that handles Metropolis updates

#pragma once
#include "Field.h"
#include <random>

class Metropolis {
    public:
        // ------------------ CONSTRUCTOR -----------------
        Metropolis(Field& phi, double epsilon, unsigned seed = 105315);

        void sweep();                                                 ///< Sweeps over all lattice points

    private:
        Field& phi_;                                                  ///< Field data reference
        std::mt19937 rng_;                                            ///< PRNG (Mersenne Twister)
        std::uniform_real_distribution<double> proposed_change_dist_; ///< Uniform distribution for proposed change eta 
        std::uniform_real_distribution<double> accept_dist_;          ///< Uniform distribution for accept / reject prob

        double propose_change();                                      ///< Alters a field value at a lattice point
        bool accept_reject(double delta_s);                           ///< Decides to keep or reject a change based on dS
};
