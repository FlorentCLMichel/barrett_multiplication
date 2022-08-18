/**
 * @file
 * @brief Small test of the power function for `unsigned char`.
 */

#include "barrett_mul.h"
#include <vector>
#include <iostream>

int main() {
    
    // run the test
    std::cout << "Running test SMALL_TEST_POW_U8... " << std::flush;
    const unsigned char q = 100;
    const unsigned char x = 3;
    const unsigned int max_power = 10;
    const std::vector<unsigned char> exp_y({1, 3, 9, 27, 81, 43, 29, 87, 61, 83, 49});
    
    const BarrettMod<unsigned char> barrett(q);
    for (unsigned int i = 0; i <= max_power; i++) {
    unsigned char y = barrett.power(x, i);
        if (y != exp_y[i]) {
            std::cout << "FAILED: (" 
                      << (unsigned int) x << " ^ " << i
                      << ") % " << (unsigned int) q 
                      << " != " << (unsigned int) y
                      << std::endl;
            return 1;
        }
    }
    std::cout << "PASSED" << std::endl;
    return 0;
}
