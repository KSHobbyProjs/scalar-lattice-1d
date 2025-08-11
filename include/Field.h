// Field.h
// Represents a scalar field on an nt x nx lattice with periodic boundary conditions.
// Supports initialization, field access, and action computation

// includes .at (reminder to change this when out of debug mode)

#pragma once
#include <vector>

class Field {
    public:
        // ----------- CONSTRUCTOR ------------------
        Field(int nt, int nx, double m = 1.0, double lambda = 1.0, double a = 1.0);

        // ----------- ACCESSORS --------------------
        double& operator()(int t, int x) {return data_.at(t * nx_ + x);}
        double operator()(int t, int x) const {return data_.at(t * nx_ + x);}
        int length_x() const {return nx_;}
        int length_t() const {return nt_;}
        double mass() const {return m_;}
        double lambda() const {return lambda_;}
        double a() const {return a_;} 
        
        // ----------- METHODS ----------------------
        double total_action() const;
        double local_action_change(int t, int x, double eta) const;

    private:
        int nt_, nx_;                   ///< dimensions
        double m_, lambda_, a_;         ///< field parameters (mass, quartic coupling, lattice spacing) 
        double mass_coeff_;             ///< coefficient for the mass term in S
        double coupling_coeff_;         ///< coefficient for the quartic coupling term in S
        std::vector<double> data_;      ///< field data
                                                      
        // ----------- Periodic BCs Methods ----
        int xleft(int x) const {return (x - 1 + nx_) % nx_;}
        int xright (int x) const {return (x + 1) % nx_;}
        int tleft (int t) const {return (t - 1 + nt_) % nt_;}
        int tright (int t) const {return (t + 1) % nt_;}
};
