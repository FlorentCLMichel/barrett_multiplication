/**
 * @file
 * @brief Test of all possible divisions of `DoubleInteger <unsigned char>` by `unsigned char`.
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
    std::cout << "Running test DIV_BY_U_U8... " << std::flush;
    unsigned char i = 0;
    do {
        unsigned char j = 0;
        do {
            DoubleInteger<unsigned char> x = DoubleInteger<unsigned char>::mul(i, j);
            unsigned int x_int = ((unsigned int) x.msb) * 256 + ((unsigned int) x.lsb);
            unsigned char k = 1;
            do {
                DoubleInteger<unsigned char> y = x.div_by_u(k);
                unsigned int y_int = ((unsigned int) y.msb) * 256 + ((unsigned int) y.lsb);
                if (x_int / k != y_int) {
                    std::cout << "FAILED: " 
                              << x_int << " / " << (unsigned int) k << " != " << y_int
                              << std::endl;
                    return 1;
                }
                ++k;
            } while (k > 0);
            ++j;
        } while (j > 0);
        ++i;
    } while (i > 0);
    std::cout << "PASSED" << std::endl;
    return 0;
}
