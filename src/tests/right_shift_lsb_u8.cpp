/**
 * @file
 * @brief Test of all possible right shifts of DoubleInteger <unsigned char>, 
 * keeping only the lsb.
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
    std::cout << "Running test RIGHT_SHIFT_LSB_U8... " << std::flush;
    unsigned char i = 0;
    do {
        unsigned char j = 0;
        do {
            DoubleInteger<unsigned char> x(i, j);
            unsigned int x_int = ((unsigned int) x.msb) * 256 + ((unsigned int) x.lsb);
            for (unsigned char k=0; k<16; k++) {
                unsigned char x_shifted = x.shift_right_lsb(k);
                if (x_shifted != ((x_int >> k) & 255)) {
                    std::cout << "FAILED: " 
                              << x_int << " >> " << (unsigned int) k << " != " << (unsigned int) x_shifted
                              << std::endl;
                    return 1;
                }
            }
            ++j;
        } while (j > 0);
        ++i;
    } while (i > 0);
    std::cout << "PASSED" << std::endl;
    return 0;
}
