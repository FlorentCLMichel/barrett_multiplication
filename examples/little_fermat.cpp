/**
 * @file
 * @brief Example of application: Checking the little Fermat theorem. 
 *
 * The little Fermat theorem states that, if \f$ p \f$ is a prime number and \f$ a \f$ an integer 
 * which is not a multiple of \f$ p \f$, then \f$ a^{p-1} \equiv 1 \; \mathrm{mod} \; p \f$. 
 *
 * This example takes one argument, a positive integer \f$ p \f$, and checks the little Fermat 
 * theorem for all integers between \f$ 1 \f$ and \f$ p-1 \f$ included.
 *
 * **Example of use:** `./little-fermat 97` 
 */

#include "barrett_mul.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Missing argument (positive integer)" << std::endl;
        return 1;
    }

    unsigned int p = std::stoi(argv[1]);
    
    if (p > 0) {
        BarrettMod<unsigned int> barrett(p);
        for (unsigned int i=1; i<p; i++) {
            unsigned int res = barrett.power(i, p-1);
            std::cout << i << "^" << p-1 << " = " << res << std::endl;
            if (res != 1) {
                std::cout << "The integer " << p << " does not seem to be a prime..." << std::endl;
                return 0;
            }
        }
    }
    std::cout << "The little Fermat theorem is verified for p = " << p << std::endl;

    return 0;
}
