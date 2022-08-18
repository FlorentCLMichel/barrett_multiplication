#include "double_integer.h"
#include <limits.h>


template<UnsignedInteger U>
DoubleInteger<U>::DoubleInteger() {}


template<UnsignedInteger U>
DoubleInteger<U>::DoubleInteger(const U& msb, const U& lsb): msb(msb), lsb(lsb)
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
DoubleInteger<U> DoubleInteger<U>::make_new(const U& new_msb, const U& new_lsb) const
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
        

template <UnsignedInteger U>
DoubleInteger<U> DoubleInteger<U>::operator>>(const U& n) const {
    if (n >= n_bits_u) {
        return make_new(zero, msb >> (n - n_bits_u));
    }
    const U rem_bits = n_bits_u - n;
    const U mask_msb_to_lsb = (one << n) - one;
    const U new_lsb = (lsb >> n) + ((msb & mask_msb_to_lsb) << rem_bits);
    const U new_msb = msb >> n;
    return make_new(new_msb, new_lsb);
}
        

template <UnsignedInteger U>
DoubleInteger<U> DoubleInteger<U>::operator<<(const U& n) const {
    if (n >= n_bits_u) {
        return make_new(lsb << (n - n_bits_u), zero);
    }
    U new_msb = msb << n;
    const U rem_bits = n_bits_u - n;
    const U mask_lsb_to_msb = ~((one << rem_bits) - one);
    new_msb += (lsb & mask_lsb_to_msb) >> rem_bits;
    const U new_lsb = (lsb & ~mask_lsb_to_msb) << n;
    return make_new(new_msb, new_lsb);
}
        

template<UnsignedInteger U>
bool DoubleInteger<U>::operator<=(const DoubleInteger<U>& other) const {
    return (msb < other.msb) || ((msb == other.msb) && (lsb <= other.lsb));
}


template<UnsignedInteger U>
DoubleInteger<U> DoubleInteger<U>::div_by_u(const U& q) const {
    const U zero = (U) 0;
    const U max_digit = ~((U) 0);
    const U one = (U) 1;
    
    if (q == one) { return *this; }

    const U new_msb = msb / q;
    const U ten_over_q = 
    ((max_digit % q) != q - one) ?
        max_digit / q
        : (max_digit / q) + one;
    U new_lsb = lsb / q + (msb % q) * ten_over_q;
    U to_add = one << (((unsigned char) (sizeof(U) * CHAR_BIT)) - one);
    const DoubleInteger<U> c1 = make_new(new_msb * q, zero);
    const DoubleInteger<U> max = make_new(max_digit, max_digit);
    while (to_add != zero) {
        U next_lsb = new_lsb + to_add;
        while ((new_lsb <= (max_digit - to_add)
                && (DoubleInteger<U>::mul(next_lsb, q) <= max - c1)
                && (DoubleInteger<U>::mul(next_lsb, q) + c1 <= *this))
            && ((DoubleInteger<U>::mul(next_lsb, q) + make_new(new_msb * q, zero)) <= *this))
        {
            new_lsb = next_lsb;
            next_lsb += to_add;
        }
        to_add >>= one;
    }
    return make_new(new_msb, new_lsb);
}


template<UnsignedInteger U>
U DoubleInteger<U>::sub_lsb(const DoubleInteger<U>& other) const {
    return lsb - other.lsb;
}


template<UnsignedInteger U>
U DoubleInteger<U>::shift_right_lsb(const U& n) const {
    if (n >= n_bits_u) {
        return msb >> (n - n_bits_u);
    }
    const U rem_bits = n_bits_u - n;
    const U mask_msb_to_lsb = (one << n) - one;
    const U new_lsb = (lsb >> n) + ((msb & mask_msb_to_lsb) << rem_bits);
    return new_lsb;
}


template<UnsignedInteger U>
DoubleInteger<U> DoubleInteger<U>::mul(const U& a, const U& b) {
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
