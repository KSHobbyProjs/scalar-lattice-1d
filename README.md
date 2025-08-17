# scalar-lattice-1d
## 1+1D Lattice QFT Simulation
This project implements a lattice quantum field theory(QFT) in 1+1 dimensions for a real, scalar field with a quartic coupling potential. It demonstrates how to numerically study quantum field theories using lattice discretization and Monte Carlo sampling techniques.
### Overview
**Theory**: We use natural units. We have a scalar field $\phi(x,t)$ with Lagrangian $\mathcal{L}= \frac{1}{2}\partial_\mu\phi\partial^\mu\phi + \frac{1}{2}m^2\phi^2 + \frac{\lambda}{4!}\phi^4$. The action is given by $S = \int d^4x L$, and the path integral goes as $\langle \phi_f; t_f|\phi_i; t_i\rangle = \int \mathcal{D}\phi e^{-i S}$. After Wick rotating time ($t\rightarrow i\tau$), we have $Z = \int \mathcal{D}\phi e^{-S}.$ $Z$ is the Euclidean path integral, and it's a partition function that allows us to calculate the expection values of observables. I.e., $\langle O\rangle = \frac{1}{Z} \int \mathcal{D}\phi O\[\phi\] e^{-S}.$ As such, $P\[\phi\] \propto e^{-S},$ which is the basis for the use of the Monte Carlo sampling techniques.

**Discretization**: Spacetime is discretized into a lattice, replacing derivatives with finite differences (we use central difference).

**Sampling**: We use the Metropolis algorithm to generate field configurations distributed according the Euclidean path integral: at each spacetime point $(t,x)$, we randomly change the field at $\phi(t,x)$. We accept the change with probability $e^{-\Delta S}$ where $\Delta S$ is the change in the action due to the change in the field value (probability is equal to 1 if $\Delta S\le 0$.).

---

### Observables **CURRENTLY STILL UNDER CONSTRUCTION**
The simulation calculates several key values to probe the field dynamics:
 - Two-point correlation functions: Measures how field values at different points are correlated (related to the probability that a particle created at $x$ propagates to $y$.).
 - Field expectation value: Average field over the lattice, $\langle \phi \rangle$ (average vacuum behavior of the field). 
 - Susceptibility: Measures response to small perturbations (useful for studying phase transitions).                         
 - Binder cumulant: Higher-order statistic that helps identify **critical behavior** and **phase transitions**.

---

### Getting Started / Implementation
Clone the repository: 
```bash 
git clone https://github.com/KSHobbyProjs/scalar-lattice-1d.git 
```
In `main.cpp`, adjust the lattice dimensions (`nt` for number of time points; `nx` for number of spatial points), Metropolis step parameter (`epsilon`), the PRNG seed (`seed`), and the number of steps for thermalization (`num_thermalize_steps`) at the top of the file. Compile with whatever C++ compiler you have. For g++ with maximum optimization:
```bash
g++ -O3 -Iinclude src/Field.cpp src/Metropolis.cpp src/Simulation.cpp main.cpp -o test
```
After running the binary, an output file will be located in `output/output.dat`. The first column is the sweep number, and the second column is $\langle \phi^2\rangle$ (the variance of the single field configuration, not the variance of the ensemble). This can be viewed with GNUplot and is helpful to see if you've set enough thermalization steps. If it hasn't plateaued, you need more steps. This is the only "observable" computed at the moment.

---
### TODO
- Move config information from main.cpp to a config file
- Set seed randomly based on device data
- Set epsilon automatically during thermalization
- Compute observables
- Create Python script to visualize data
- Create makefile
- Make the README (this!) more clear on thermalization

#### This project was made in an effort to self-learn lattice QFT methods and C++. It has little to no practical use for other people.
Made in August of 2025.
