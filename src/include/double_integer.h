#ifndef __DOUBLE_INTEGER_H_
#define __DOUBLE_INTEGER_H_

/**
 * @file
 * @brief defines a class for double-size integers
 */

#include "unsigned_integer_concept.h"

/** 
 * A partial implementation of double-size unsigned integers
 * @tparam U unsigned integer type to work with
 */
template<UnsignedInteger U>
class DoubleInteger {
    public:

        /// most significant bits
        U msb;

        /// least significant bits
        U lsb;

        DoubleInteger();

        /**
         * @brief Constructor from two single-size integers.
         * @param msb most significant bits
         * @param lsb least significant bits
         */
        DoubleInteger(const U msb, const U lsb);

        /**
         * @brief Builds a new double-size integer.
         * @param msb most significant bits
         * @param lsb least significant bits
         */
        const DoubleInteger<U> make_new(const U msb, const U lsb);

        /**
         * @brief addition
         *
         * We assume the result does not overflow.
         */
        const DoubleInteger<U> operator+(const DoubleInteger<U>& other);
        
        /**
         * @brief subtraction
         *
         * We assume the result is non-negative.
         */
        const DoubleInteger<U> operator-(const DoubleInteger<U>& other);
        
        /**
         * @brief right bit shifting
         */
        const DoubleInteger<U> operator>>(const U& n);
        
        /**
         * @brief left bit shifting
         */
        const DoubleInteger<U> operator<<(const U& n);

    private: 
        U zero;
        U one;
        U two;
        U n_bits_u;
        U n_bits_u_minus_1;
        U mask_highest_bit_u;
        U mask_low_bits_u;
};


/**
 * Generate a #DoubleInteger by multiplying two single-size integers
 * @param a left multiplicant
 * @param b right multiplicant
 */
template<UnsignedInteger U>
DoubleInteger<U> mul(U& a, U& b);


/// Implementations for the usual types
template class DoubleInteger<unsigned char>;
template class DoubleInteger<unsigned int>;
template class DoubleInteger<unsigned long>;
template class DoubleInteger<unsigned long long>;

#endif
