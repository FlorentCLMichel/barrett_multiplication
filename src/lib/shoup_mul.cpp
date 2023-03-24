#include "shoup_mul.h"


template<UnsignedInteger U>
ShoupMul<U>::ShoupMul(const U q, const U w, const unsigned int log_2_beta) : 
    q(q), w(w), log_2_beta(log_2_beta)
{
    U beta = ((U) 1) << log_2_beta;
    wp = DoubleInteger<U>::mul(w, beta).div_by_u(q).lsb;
}


template<UnsignedInteger U>
U ShoupMul<U>::mod_mul(const U& x) const {
    DoubleInteger<U> w_x = DoubleInteger<U>::mul(w, x);
    U c = (DoubleInteger<U>::mul(wp, x) >> log_2_beta).lsb;
    DoubleInteger<U> c_q = DoubleInteger<U>::mul(c, q);
    U g_x = (w_x - c_q).lsb;
    return g_x < q ? g_x : g_x - q;
}
