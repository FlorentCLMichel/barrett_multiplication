#ifndef __BARRETT_CLASS_H_
#define __BARRETT_CLASS_H_

/**
 * @file
 * @brief definition of the `BarrettMod` class
 */

#include "unsigned_integer_concept.h"
#include "double_integer.h"

template<UnsignedInteger U>
class BarrettMod {
    public: 

        /// modulus
        const U q;

        /** constructor
         * @param q modulus; must be larger than 2 and smaller than or equal to 2^b / 3, 
         *  where $b$ is the number of bits of the type `U`.
         */
        BarrettMod(const U q);
        
        /** reduction modulo `q` of a single-size integer
         * @param x number to be reduced modulo `q`; must be smaller than `q*q`
         */
        U mod_red(const U& x) const;

        /** reduction modulo `q` of a double-size integer
         * @param x number to be reduced modulo `q`; should be no larger than `2^b / 3`
         */
        U mod_red_d(const DoubleInteger<U>& x) const;

        /** multiplication modulo `q`
         * @param a left input for the multiplication; must be smaller than `q`
         * @param b right input for the multiplication; must be smaller than `q`
         */
        U mod_mul(const U& a, const U& b) const;

        /** compute x to the power k and return the result modulo q
         * @param x input
         * @param k ewponent
         */
        U power(const U& x, unsigned int k) const;

    private: 

        U log_2_q;
        U log_2_q_plus_2;
        U k;
};


/// Implementations of the `BarrettMod` class for the usual types
template class BarrettMod<unsigned char>;
template class BarrettMod<unsigned int>;
template class BarrettMod<unsigned long>;
template class BarrettMod<unsigned long long>;

#endif
