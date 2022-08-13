/**
 * @file
 * @brief Test of all possible additions for DoubleInteger <unsigned char>.
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
            DoubleInteger<unsigned char> a(i, j);
            unsigned int a_int = ((unsigned int) i) * 256 + ((unsigned int) j);
            unsigned char k = 0;
            do {
                unsigned char l = 0;
                do {
                     unsigned int b_int = ((unsigned int) k) * 256 + ((unsigned int) l);
                     if (a_int + b_int < 256*256) {
                        DoubleInteger<unsigned char> b(k, l);
                        DoubleInteger<unsigned char> c = a + b;
                        unsigned int c_int = ((unsigned int) c.msb) * 256 + ((unsigned int) c.lsb);
                        if (a_int + b_int != c_int) {
                            std::cout << "TEST ADD_DOUBLE_U8 FAILED: " 
                                      << a_int << " + " << b_int << " != " << c_int 
                                      << std::endl;
                            return 1;
                        }
                     }
                     ++l;
                } while (l > 0);
                ++k;
            } while (k > 0);
            ++j;
        } while (j > 0);
        ++i;
    } while (i > 0);
    std::cout << "TEST ADD_DOUBLE_U8 PASSED" << std::endl;
    return 0;
}
