#ifndef SHOUP_MUL_H
#define SHOUP_MUL_H

/**
 * @file
 * @brief definition of the `ShoupMul` class for Shoup multiplication
 */

#include "unsigned_integer_concept.h"
#include "double_integer.h"

template<UnsignedInteger U>
class ShoupMul {
    public: 
        /// modulus
        const U q;

        /// factor
        const U w;
        
        /** constructor
         * @param q modulus
         * @param w factor
         * @param log_2_beta logarithm of beta in base 2
         */
        ShoupMul(const U q, const U w, const unsigned int log_2_beta);

        /** multiplication by `w` modulo `q`
         * @param x input
         */
        U mod_mul(const U& x) const;

    private:
        U wp;
        const unsigned int log_2_beta;
};

/// Implementations of the `ShoupMul` class for the usual types
template class ShoupMul<unsigned char>;
template class ShoupMul<unsigned int>;
template class ShoupMul<unsigned long>;
template class ShoupMul<unsigned long long>;

#endif
