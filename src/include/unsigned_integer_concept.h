#ifndef __UNSIGNED_INTEGERS_CONCEPT_H_
#define __UNSIGNED_INTEGERS_CONCEPT__h
 
/** 
 * @file
 * @brief definition of the `UnsignedInteger` concept
 */

#include<climits>
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
 *  * the comparison operator `<`
 */
template<typename T>
concept UnsignedInteger = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>; 
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a << b } -> std::convertible_to<T>; 
    { a >> b } -> std::convertible_to<T>; 
    a += b; 
    a -= b; 
    a *= b;
    a <<= b;
    a >>= b;
    { a < b } -> std::convertible_to<bool>;
    { sizeof(a) } -> std::convertible_to<unsigned int>;
} && std::convertible_to<unsigned char, T>;

#endif
