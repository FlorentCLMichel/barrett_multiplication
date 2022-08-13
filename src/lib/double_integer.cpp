#include "double_integer.h"
#include <limits.h>

template<UnsignedInteger U>
DoubleInteger<U>::DoubleInteger(const U& msb, const U& lsb): msb(msb), lsb(lsb)
{
    zero = (U) 0;
    one = (U) 1;
    two = (U) 2;
    n_bits_u = (U) (sizeof(U) * CHAR_BIT);
    mask_highest_bit_u = one << (n_bits_u - one);
    n_bits_u_minus_1 = n_bits_u - one;
    mask_low_bits_u = !mask_highest_bit_u;
}
