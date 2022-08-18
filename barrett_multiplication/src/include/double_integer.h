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
        DoubleInteger(const U& msb, const U& lsb);

        /**
         * @brief Builds a new double-size integer.
         * @param msb most significant bits
         * @param lsb least significant bits
         */
        DoubleInteger<U> make_new(const U& msb, const U& lsb) const;

        /**
         * @brief addition
         *
         * We assume the result does not overflow.
         */
        DoubleInteger<U> operator+(const DoubleInteger<U>& other) const;
        
        /**
         * @brief subtraction
         *
         * We assume the result is non-negative.
         */
        DoubleInteger<U> operator-(const DoubleInteger<U>& other) const;
        
        /**
         * @brief right bit shifting
         */
        DoubleInteger<U> operator>>(const U& n) const;
        
        /**
         * @brief left bit shifting
         */
        DoubleInteger<U> operator<<(const U& n) const;
        
        /**
         * @brief smaller than or equal to comparison operator
         */
        bool operator<=(const DoubleInteger<U>& other) const;

        /**
         * @brief division by a single-size integer
         *
         * This function is not optimized, and assumed to be called very infrequently.
         */
        DoubleInteger<U> div_by_u(const U& q) const;

        /**
         * @brief subtraction, retaining only the lsb
         */
        U sub_lsb(const DoubleInteger<U>& other) const;
        
        /**
         * @right shift, retaining only the lsb
         */
        U shift_right_lsb(const U& n) const;

        /**
         * Generate a #DoubleInteger by multiplying two single-size integers
         * @param a left multiplicant
         * @param b right multiplicant
         */
        static DoubleInteger<U> mul(const U& a, const U& b);

    private: 
        U zero;
        U one;
        U two;
        U n_bits_u;
        U n_bits_u_minus_1;
        U mask_highest_bit_u;
        U mask_low_bits_u;
};


/// Implementations of the `DoubleInteger` class for the usual types
template class DoubleInteger<unsigned char>;
template class DoubleInteger<unsigned int>;
template class DoubleInteger<unsigned long>;
template class DoubleInteger<unsigned long long>;

#endif
