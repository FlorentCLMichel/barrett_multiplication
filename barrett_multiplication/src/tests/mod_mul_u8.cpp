/**
 * @file
 * @brief Test of all possible modular multiplications for `unsigned char`.
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
    std::cout << "Running test MOD_RED_D_U8... " << std::flush;
    for (unsigned char q = 3; q <= 128; q++) {
        BarrettMod<unsigned char> barrett(q);
        unsigned int q_2 = ((unsigned int) q) * ((unsigned int) q);
        unsigned char x = 0;
        do {
            unsigned char y = 0;
            do {
                unsigned int z_int = ((unsigned int) x) * ((unsigned int) y);
                if (z_int >= q_2) {
                    break;
                }
                unsigned char z_q = barrett.mod_mul(x, y);
                unsigned int z_q_int = (unsigned int) z_q;
                if (z_q_int != z_int % q) {
                    std::cout << "FAILED: " 
                              << '(' << (unsigned int) x 
                              << " * " << (unsigned int) y 
                              << ") % " << (unsigned int) q 
                              << " != " << z_q_int
                              << std::endl;
                    return 1;
                }
                ++y;
            } while (y>0);
            ++x;
        } while (x > 0);
    }
    std::cout << "PASSED" << std::endl;
    return 0;
}
