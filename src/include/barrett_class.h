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

        /// constructor
        BarrettMod(const U q);

        /** reduction modulo `q`
         * @param x number to be reduced modulo `q`
         */
        U mod_red(const DoubleInteger<U>& x) const;

        /** multiplication modulo `q`
         * @param a left input for the multiplication
         * @param b right input for the multiplication
         */
        U mod_mul(const U& a, const U& b) const;

    private: 

        const U log_2_q;
        const U log_2_q_plus_2;
        const U k;
};

#endif
