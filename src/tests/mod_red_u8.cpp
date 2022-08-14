/**
 * @file
 * @brief Test of all possible modular reductions for unsigned char`.
 */

#include "barrett_mul.h"
#include <iostream>
#include <cassert>

int main() {
    
    // check two's complement
    unsigned char x = 255;
    ++x;
    assert(x == 0);

    // run the test
    std::cout << "Running test MOD_RED_U8... " << std::flush;
    for (unsigned char q = 3; q <= 128; q++) {
        BarrettMod<unsigned char> barrett(q);
        unsigned int q_2 = ((unsigned int) q) * ((unsigned int) q);
        unsigned char x = 0;
        do {
            if (((unsigned int) x) >= q_2) {
                break;
            }
            unsigned char y = barrett.mod_red(x);
            if (y != x % q) {
                std::cout << "FAILED: " 
                          << (unsigned int) x << " % " << (unsigned int) q << " != " << (unsigned int) y
                          << std::endl;
                return 1;
            }
            ++x;
        } while (x > 0);
    }
    std::cout << "PASSED" << std::endl;
    return 0;
}
