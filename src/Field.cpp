/**
 * @class Field
 * @brief Stores and manipulates a real scalar field on a 2D lattice (time × space).
 *
 * The field is stored as a flattened 1D array in row-major order (time-major).
 * Provides accessors for field values, utilities for periodic indexing,
 * and routines for action evaluation.
 */

#include "Field.h"
// ----------- CONSTRUCTOR ---------------------
Field::Field(int nt, int nx, double m, double lambda, double a)
    : nt_(nt), nx_(nx), m_(m), lambda_(lambda), a_(a),
    mass_coeff_(0.5 * a_*a_ * m_*m_), coupling_coeff_(a_*a_ * lambda_ / 24.0),       ///< caching this rather than computing it every time
    data_(nt * nx, 0.0) {}                                                           ///< in local_action_change is a negligible time save but it looks cleaner anyway

// ----------- FIELD METHODS -------------------
double Field::total_action() const {                     ///< computes the total action
    double tot_action = 0.0;

    for (int t = 0; t < nt_; ++t) {
        for (int x = 0; x < nx_; ++x) {
            double phi = (*this)(t, x);                  ///< field at (t, x)
            double phi2 = phi * phi;                     ///< field at (t, x) squared

            double phi_tleft = (*this)(tleft(t), x);     ///< field at (t - 1, x) (w/ periodic BCs)
            double phi_tright = (*this)(tright(t), x);   ///< field at (t + 1, x) (w/ periodic BCs)
            double phi_xleft = (*this)(t, xleft(x));     ///< field at (t, x - 1) (w/ periodic BCs)
            double phi_xright = (*this)(t, xright(x));   ///< field at (t, x + 1) (w/ periodic BCs)

            double dphi_dt = phi_tright - phi_tleft;     ///< partial derivative of phi wrt t
            double dphi_dx = phi_xright - phi_xleft;     ///< partial derivative of phi wrt x
            
            tot_action += 0.125 * (dphi_dt * dphi_dt     ///< change in total action per point t, x
                +  dphi_dx * dphi_dx)
                + mass_coeff_ * phi2
                + coupling_coeff_ * phi2 * phi2;
        }
    }
    return tot_action;
}


double Field::local_action_change(int t, int x, double eta) const {              ///< computes the change in action due to a change by eta at (t, x)
    double phi = (*this)(t, x);
    double phi2 = phi * phi;
    
    double phi_x2right = (*this)(t, xright(xright(x)));                          ///< neighbor (t, x + 2)
    double phi_x2left = (*this)(t, xleft(xleft(x)));                             ///< neighbor (t, x - 2)
    double phi_t2left = (*this)(tleft(tleft(t)), x);                             ///< neighbor (t - 2, x)
    double phi_t2right = (*this)(tright(tright(t)), x);                          ///< neighbor (t + 2, x)
    
    double new_phi = phi + eta;
    double new_phi2 = new_phi * new_phi;
    double neighbor_sum = phi_x2right + phi_x2left + phi_t2right + phi_t2left;

    double local_action_change = 0.5*eta*eta + eta*phi - 0.25*eta*neighbor_sum   ///< local action change due to kinetic term
        + mass_coeff_ * (new_phi2 - phi2)                                        ///< local action change due to mass term
        + coupling_coeff_ * (new_phi2 * new_phi2 - phi2 * phi2);                 ///< local action change due to coupling term
                                                                                 
    return local_action_change;
}

