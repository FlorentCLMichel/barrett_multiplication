#include "double_integer.h"
#include <limits.h>


template<UnsignedInteger U>
DoubleInteger<U>::DoubleInteger() {}


template<UnsignedInteger U>
DoubleInteger<U>::DoubleInteger(const U msb, const U lsb): msb(msb), lsb(lsb)
{
    zero = (U) 0;
    one = (U) 1;
    two = (U) 2;
    n_bits_u = (U) (sizeof(U) * CHAR_BIT);
    mask_highest_bit_u = one << (n_bits_u - one);
    n_bits_u_minus_1 = n_bits_u - one;
    mask_low_bits_u = ~mask_highest_bit_u;
}


template<UnsignedInteger U>
const DoubleInteger<U> DoubleInteger<U>::make_new(const U new_msb, const U new_lsb)
{
    DoubleInteger<U> other;
    other.msb = new_msb;
    other.lsb = new_lsb;
    other.zero = zero;
    other.one = one;
    other.two = two;
    other.n_bits_u = n_bits_u;
    other.mask_highest_bit_u = mask_highest_bit_u;
    other.n_bits_u_minus_1 = n_bits_u_minus_1;
    other.mask_low_bits_u = mask_low_bits_u;

    return other;
}


#include <iostream>
template<UnsignedInteger U>
const DoubleInteger<U> DoubleInteger<U>::operator-(const DoubleInteger<U>& other) {

    // version assuming two's complement
    return make_new(
        msb - other.msb - (lsb < other.lsb),
        lsb - other.lsb
    );

    // // version not assuming two's complement
    // if (lsb < other.lsb) {
    //     return make_new(
    //         msb - other.msb - one,
    //         ~zero - other.lsb + lsb + one
    //     );
    // } else {
    //     return make_new(
    //         msb - other.msb,
    //         lsb - other.lsb
    //     );
    // }
}
