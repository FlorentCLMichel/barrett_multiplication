/**
 * @file
 * @brief Test of all possible products of <unsigned char>.
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
            DoubleInteger<unsigned char> x = mul(i, j);
            unsigned int x_int = ((unsigned int) x.msb) * 256 + ((unsigned int) x.lsb);
            if (x_int != ((unsigned int) i) * ((unsigned int) j)) {
                std::cout << "TEST MUL_U8 FAILED: " 
                          << (unsigned int) i << " × " << (unsigned int) j << " != " << x_int
                          << std::endl;
                return 1;
            }
            ++j;
        } while (j > 0);
        ++i;
    } while (i > 0);
    std::cout << "TEST MUL_U8 PASSED" << std::endl;
    return 0;
}
