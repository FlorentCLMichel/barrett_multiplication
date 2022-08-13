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
DoubleInteger<U> DoubleInteger<U>::make_new(const U new_msb, const U new_lsb) const
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


template<UnsignedInteger U>
DoubleInteger<U> DoubleInteger<U>::operator+(const DoubleInteger<U>& other) const {
    U new_lsb = (lsb & mask_low_bits_u) + (other.lsb & mask_low_bits_u);
    U new_msb = msb + other.msb;
    U carries = ((lsb & mask_highest_bit_u) >> n_bits_u_minus_1)
                + ((other.lsb & mask_highest_bit_u) >> n_bits_u_minus_1)
                + ((new_lsb & mask_highest_bit_u) >> n_bits_u_minus_1);
    if (carries & one == one) {
        new_lsb |= mask_highest_bit_u;
    } else {
        new_lsb &= mask_low_bits_u;
    }
    if (zero < carries >> one) {
        new_msb += one;
    }
    return make_new(new_msb, new_lsb);
}


template<UnsignedInteger U>
DoubleInteger<U> DoubleInteger<U>::operator-(const DoubleInteger<U>& other) const {

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


template<UnsignedInteger U>
DoubleInteger<U> mul(U& a, U& b) {
    const U one = 1;
    const U half_n_bits = (sizeof(U) * CHAR_BIT) >> 1;
    const U full_mask = ~((U) 0);
    const U lsb_mask = full_mask >> half_n_bits;
    const U msb_1 = a >> half_n_bits;
    const U msb_2 = b >> half_n_bits;
    const U lsb_1 = a & lsb_mask;
    const U lsb_2 = b & lsb_mask;
    const U coeff_0 = lsb_1 * lsb_2;
    const U x = lsb_1 * msb_2;
    const U y = lsb_2 * msb_1;
    const U coeff_1 = (x & lsb_mask) + (y & lsb_mask);
    const U coeff_2 = msb_1 * msb_2 + (x >> half_n_bits) + (y >> half_n_bits);
    const DoubleInteger<U> a1 = DoubleInteger<U>(coeff_2, coeff_0);
    const DoubleInteger<U> a2 = a1.make_new(coeff_1 >> half_n_bits, (coeff_1 & lsb_mask) << half_n_bits);
    return a1 + a2;
}


// Implementations of mul for the usual types
template DoubleInteger<unsigned char> mul(unsigned char&, unsigned char&);
template DoubleInteger<unsigned int> mul(unsigned int&, unsigned int&);
template DoubleInteger<unsigned long> mul(unsigned long&, unsigned long&);
template DoubleInteger<unsigned long long> mul(unsigned long long&, unsigned long long&);
