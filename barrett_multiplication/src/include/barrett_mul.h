/**
 * @mainpage
 *
 * Implementation of the Barrett modular reduction and multiplication. 
 * Given a modulus q, the objective is to compute multiplications of integers between 0 and q-1 
 * (included) using only bit-shiftings, additions, subtractions, multiplications, and comparisons. 
 * To this end, we define a class `BarrettMod` (with an unsigned integer template parameter) 
 * storing three numbers which allow to fund an approximation of the division of a number between 0 
 * and q²-1 (included) by q using one multiplication and two biy-shiftings. 
 * We also implemet a partial double-sized integers class (`DoubleInteger`) to represent the 
 * product of two integers and an `UnsignedInteger` concept (see `unsigned_integer_concept.h`).
 *
 * Building this project requires
 *
 * * Cmake version 3.22+
 * * A C++20 compiler with two's complement for unsigned integers
 */


#ifndef __BARRETT_MUL_H_
#define __BARRETT_MUL_H_

/**
 * @file
 * @brief the main include file
 */

#include "hello_world.h"
#include "unsigned_integer_concept.h"
#include "double_integer.h"
#include "barrett_class.h"

#endif
