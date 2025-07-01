#!/usr/bin/env python
#
# simulates a scalar, quartic-potential field theory on a lattice and calculates expectation values for known parameters
#
# Copyright K. Scarbro; 2025--

"""
A module that simulates a field theory with Lagrangian density (L = Kinetic + Mass + Lambda / 4! phi^4) in 1+1D. We Wick rotate time, and use sample different field
configurations using the Metropolis algorithm. Different observables are calculates similarly.

Required Packages:

Syntax:

Output:

K. Scarbro 7.1.25
"""

# IMPORTS
import sys, os

def main(args):
    pass


if __name__ == "__main__":
    if len(sys.argv) < 2 or sys.argv[1].endswith("help"):
        print(__doc__)
    else:
        main(sys.argv[1:])
