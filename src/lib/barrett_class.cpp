#include "barrett_class.h"

template<UnsignedInteger U>
BarrettMod<U>::BarrettMod(const U q) : q(q) {
    const U one = (U) 1;
    const U two = (U) 2;
    log_2_q = log_2(q) - one;
    const U one_shifted = one << (log_2_q + one);
    k = DoubleInteger<U>::mul(one_shifted, one_shifted).div_by_u(q).lsb;
    log_2_q_plus_2 = log_2_q + two;
}


template<UnsignedInteger U>
U BarrettMod<U>::mod_red(const U& x) const {
    const U z = x >> log_2_q;
    const U y = (z * k) >> log_2_q_plus_2;
    U c = x - (y * q);
    if (q <= c) { c -= q; }
    return q <= c ? c - q : c;
}


template<UnsignedInteger U>
U BarrettMod<U>::mod_red_d(const DoubleInteger<U>& x) const {
    const U z = x.shift_right_lsb(log_2_q);
    const U y = DoubleInteger<U>::mul(z, k).shift_right_lsb(log_2_q_plus_2);
    const DoubleInteger<U> a = DoubleInteger<U>::mul(y, q);
    U c = x.sub_lsb(a);
    if (q <= c) { c -= q; }
    return q <= c ? c - q : c;
}
        

template<UnsignedInteger U>
U BarrettMod<U>::mod_mul(const U& a, const U& b) const {
    DoubleInteger<U> c = DoubleInteger<U>::mul(a, b);
    return mod_red_d(c);
}

template<UnsignedInteger U>
U BarrettMod<U>::power(const U& x, unsigned int k) const {
    U y = (U) 1;
    U x_pow2 = x;
    while (k != 0) {
        if (k & 1 != 0) {
            y = mod_mul(y, x_pow2);
        }
        x_pow2 = mod_mul(x_pow2, x_pow2);
        k >>= 1;
    }
    return y;
}
