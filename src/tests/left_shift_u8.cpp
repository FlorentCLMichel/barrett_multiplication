/**
 * @file
 * @brief Test of all possible left shifts of DoubleInteger <unsigned char>.
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
    std::cout << "Running test LEFT_SHIFT_U8... " << std::flush;
    unsigned char i = 0;
    do {
        unsigned char j = 0;
        do {
            DoubleInteger<unsigned char> x(i, j);
            unsigned int x_int = ((unsigned int) x.msb) * 256 + ((unsigned int) x.lsb);
            for (unsigned char k=0; k<16; k++) {
                if (x_int << k < 256*256) {
                    DoubleInteger<unsigned char> x_shifted = x << k;
                    unsigned int x_shifted_int = ((unsigned int) x_shifted.msb) * 256 + ((unsigned int) x_shifted.lsb);
                    if (x_shifted_int != x_int << k) {
                        std::cout << "FAILED: " 
                                  << x_int << " >> " << (unsigned int) k << " != " << x_shifted_int
                                  << std::endl;
                        return 1;
                    }
                }
            }
            ++j;
        } while (j > 0);
        ++i;
    } while (i > 0);
    std::cout << "PASSED" << std::endl;
    return 0;
}
