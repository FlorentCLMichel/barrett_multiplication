#include "unsigned_integer_concept.h"

template<UnsignedInteger U>
U log_2(const U& x) {
    const U zero = (U) 0;
    const U one = (U) 1;
    U res = zero;
    U y = one;
    while (y < x) {
        res += one;
        y <<= one;
    }
    return res;
}


// implementation for the main unsigned integer types
template unsigned char log_2(const unsigned char&);
template unsigned int log_2(const unsigned int&);
template unsigned long log_2(const unsigned long&);
template unsigned long long log_2(const unsigned long long&);
