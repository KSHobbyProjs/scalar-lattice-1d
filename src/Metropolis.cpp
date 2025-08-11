/**
 * @class Metropolis
 * @brief Handles metropolis updates over a real scalar field on a 2D lattice (time × space).
 *
 * The class takes the field by reference
 */

#include "Metropolis.h"
#include "Field.h"
#include <cmath>
// --------------------------- CONSTRUCTOR -------------------------------
Metropolis::Metropolis(Field& phi, double epsilon, unsigned seed)
    : phi_(phi), rng_(seed), proposed_change_dist_(-epsilon, epsilon), accept_dist_(0.0, 1.0) {}

// --------------------------- FIELD METHODS -----------------------------
void Metropolis::sweep() {
    int nt = phi_.length_t();
    int nx = phi_.length_x();
    for (int t = 0; t < nt; ++t) {
        for (int x = 0; x < nx; ++x) { 
            double eta = propose_change();
            double delta_s = phi_.local_action_change(t, x, eta);
            bool accept = accept_reject(delta_s);

            if (accept) {
                   phi_(t, x) += eta;
            }
        }
    }
}

double Metropolis::propose_change() {
    double eta = proposed_change_dist_(rng_);
    return eta;
}

bool Metropolis::accept_reject(double delta_s) {
    if (delta_s <= 0) {
        return true;                            ///< return true always if action decreases
    }
    else {
        double r = accept_dist_(rng_);
        return r < std::exp(-delta_s);          ///< return true with prob exp(-delta_s) if action increases
    }
}



