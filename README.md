# scalar-lattice-1d
## 1+1D Lattice QFT Simulation
This project implements a lattice quantum field theory(QFT) in 1+1 dimensions for a real, scalar field with a quartic coupling potential. It demonstrates how to numerically study quantum field theories using lattice discretization and Monte Carlo sampling techniques.
### Overview
**Theory**: Scalar field $\phi(x,t)$ with Lagrangian 
$$
  L = \frac{1}{2}\partial_\mu\phi\partial^\mu\phi + \frac{1}{2}m^2\phi^2 + \frac{\lambda}{4!}\phi^4.
$$
A lattice qft simulation in 1+1D with a scalar quartic-potential Lagrangian. We discretize spacetime into a lattice, and use Monte Carlo techniques (metropolis algorithm) to sample field configurations from the Euclidean path integral. We calculate two-point correlation functions, field expectation values, susceptibility, and the Binder cumulant.
