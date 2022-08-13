/**
 * @file
 * @brief Test of all possible right shifts of DoubleInteger <unsigned char>.
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
    unsigned char i = 0;
    do {
        unsigned char j = 0;
        do {
            DoubleInteger<unsigned char> x(i, j);
            unsigned int x_int = ((unsigned int) x.msb) * 256 + ((unsigned int) x.lsb);
            for (unsigned char k=0; k<16; k++) {
                DoubleInteger<unsigned char> x_shifted = x >> k;
                unsigned int x_shifted_int = ((unsigned int) x_shifted.msb) * 256 + ((unsigned int) x_shifted.lsb);
                if (x_shifted_int != x_int >> k) {
                    std::cout << "TEST RIGHT_SHIFT_U8 FAILED: " 
                              << x_int << " >> " << (unsigned int) k << " != " << x_shifted_int
                              << std::endl;
                    return 1;
                }
            }
            ++j;
        } while (j > 0);
        ++i;
    } while (i > 0);
    std::cout << "TEST RIGHT_SHIFT_U8 PASSED" << std::endl;
    return 0;
}
