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


#include <iostream>
template<UnsignedInteger U>
U BarrettMod<U>::mod_red(const U& x) const {
    const U z = x >> log_2_q;
    const U y = (z * k) >> log_2_q_plus_2;
    U c = x - (y * q);
    if (q <= c) { c -= q; }
    return q <= c ? c - q : c;
}
