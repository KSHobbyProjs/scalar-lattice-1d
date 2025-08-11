#include <iostream>
#include "Field.h"

int main() {
    Field phi(10, 5); // create a 10x5 field
    std::cout << "phi(2,2) from 1.0 to 0.0 " << phi.local_action_change(2, 2, 1.0) << std::endl;
    // phi(2,3) = 42.0; // set a value
    std::cout << "phi(5,0) = " << phi(5,0) << std::endl;
    
    std::cout << "Length in x: " << phi.length_x() << std::endl;
    std::cout << "Length in t: " << phi.length_t() << std::endl;
    std::cout << "mass: " << phi.mass() << std::endl;
    std::cout << "lambda: " << phi.lambda() << std::endl;

    std::cout << "total action: " << phi.total_action() << std::endl;

    return 0;
}
