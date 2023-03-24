/**
 * @file
 * @brief Test of all possible modular multiplications for `u8`s.
 */

#include "shoup_mul.h"
#include <iostream>
#include <cassert>

int main() {

    // run the test
    std::cout << "Running test SHOUP_MUL_U8... " << std::flush;
    for (unsigned char q = 3; q <= 127; q++) {
        for (unsigned char w = 0; w < q; w++) {
            ShoupMul<unsigned char> shoup(q, w, 7);
            for (unsigned char x = 0; x < q; x++) {
                unsigned char y = shoup.mod_mul(x);
                if (y != (x*w) % q) {
                    std::cout << "FAILED: " 
                              << (unsigned int) w << " × " 
                              << (unsigned int) x << " % " 
                              << (unsigned int) q << " != " 
                              << (unsigned int) y << std::endl;
                    return 1;
                }
            }
        }
    }
    std::cout << "PASSED" << std::endl;
    return 0;
}
