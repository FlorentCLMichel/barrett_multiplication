#ifndef UNSIGNED_INTEGERS_CONCEPT_H
#define UNSIGNED_INTEGERS_CONCEPT_H
 
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
 *  * addition, subtraction, and multiplication
 *  * the bit-wise operations `!`, `&`, `|`, and `^`
 *  * left and right bit shift
 *  * the comparison operators `<`, `<=`, `==`, and `!=`
 *  * conversion from an `unsigned char` or a `bool`
 */
template<typename T>
concept UnsignedInteger = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>; 
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { !a } -> std::convertible_to<T>;
    { a & b } -> std::convertible_to<T>;
    { a | b } -> std::convertible_to<T>;
    { a ^ b } -> std::convertible_to<T>;
    { a << b } -> std::convertible_to<T>; 
    { a >> b } -> std::convertible_to<T>; 
    a += b; 
    a -= b; 
    a *= b;
    a &= b;
    a |= b;
    a ^= b;
    a <<= b;
    a >>= b;
    { a < b } -> std::convertible_to<bool>;
    { a <= b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
    { sizeof(a) } -> std::convertible_to<unsigned int>;
} && std::convertible_to<unsigned char, T> && std::convertible_to<bool, T>;


/// ceil of the logarithm in base 2
template<UnsignedInteger U>
U log_2(const U&);

#endif
