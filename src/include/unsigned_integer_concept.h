#ifndef __UNSIGNED_INTEGERS_CONCEPT_H_
#define __UNSIGNED_INTEGERS_CONCEPT__h
 
/** 
 * @file
 * @brief definition of the `UnsignedInteger` concept
 */

#include<concepts>

/**
 *  A concept for data typs which may be used as unsigned integers. 
 *
 *  They must implement
 *  * addition
 *  * subtraction
 *  * multiplication
 *  * left bit shift
 *  * right bit shift
 */
template<typename T>
concept UnsignedInteger = requires(T x) {
    { std::operator+(const T y) } -> std::convertible_to<T>;
};

#endif
