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
        Metropolis(double epsilon, unsigned seed = 10531);

        // ------------------ UPDATE METHODS ---------------
        void sweep(Field& phi);                                       ///< Metropolis sweep over all lattice points
        
        double acceptance_rate() const;                               ///< calculates the Metropolis acceptance rate
        void reset_acceptance_rate();                                 ///< resets the Metropolis acceptance rate

    private:
        std::mt19937 rng_;                                                  ///< PRNG (Mersenne Twister)
        std::uniform_real_distribution<double> proposed_change_dist_; ///< uniform distribution for proposed change eta 
        std::uniform_real_distribution<double> accept_dist_;          ///< uniform distribution for accept / reject prob
        unsigned proposed_states_, accepted_states_;                        ///< counters to keep track of Metropolis acceptance rate

        // ------------------ UPDATE METHODS ---------------
        double propose_change();                                      ///< alters a field value at a lattice point
        bool accept_reject(double delta_s);                           ///< decides to keep or reject a change based on dS
};
