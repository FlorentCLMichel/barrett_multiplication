# Barrett Multiplication

This is a simple example of C++ code to compute the product of two integers modulo a third one using only ‘fast’ operations (right bit shifting, addition, subtraction, multilication, and comparison). 

## A bit of theory

Let $q$ be a positive integer larger than $1$. Let $w$ be the logarithm of $q$ in base $2$, rounded up. Let $a$ and $b$ be two non-negative integers smaller than $q$. We want to compute the product of $a$ and $b$ modulo $q$, *i.e.*, the remainder of the Euclidean division of $a \times b$ by $q$.

We proceeed as follows. First, we pre-compute $w$ and the integer $k$  given by $k = \lfloor 2^{2 w} / q \rfloor$. We then compute the following quantities: 

$$
    x_1 = a \times b
$$

$$
    x_2 = \lfloor x_1 / 2^{w-1} \rfloor
$$

$$
    x_3 = \lfloor (x_2 \times k) / 2^{w+1} \rfloor
$$

$$
    c = x_1 - x_3 \times q.
$$

Obviously, $c \equiv a \times b \; \mathrm{mod} \; q$. Moreover, we have

$$
    \frac{x_2 \times k}{2^{w+1}} - 1 < x_3 \leq \frac{x_2 \times k}{2^{w+1}}
$$

and 

$$
    \frac{a \times b}{2^{w-1}} - 1 < x_2 \leq \frac{a \times b}{2^{w-1}},
$$

so

$$
    \frac{a \times b \times k}{2^{2 w}} - \frac{k}{2^{w+1}} - 1 < x_3 \leq \frac{a \times b \times k}{2^{2 w}}.
$$

Since 

$$
    \frac{2^{2 w}}{q} - 1 < k \leq \frac{2^{2 w}}{q},
$$

this gives

$$
    \frac{a \times b}{q} - \frac{a \times b}{2^{2 w}} - \frac{2^w}{2 q} - 1 < x_3 \leq \frac{a \times b}{q}.
$$

Since $a$ and $b$ are both smaller than $2^w$, this gives

$$
    \frac{a \times b}{q} - 2 - \frac{2^w}{2 q} < x_3 \leq \frac{a \times b}{q}.
$$

So, 

$$
    a \times b - 2 q - 2^{w-1} < q \times x_3 \leq a \times b.
$$

Since $w$ is the logarithm of $q$ in base $2$ rounded up, $2^{w-1} < q$.

We conclude that 

$$
    3 q > c \geq 0.
$$

So, either $c$, $c - q$, or $c - 2 q$ is in the range $[0, q)$, and thus equal to the reduction of $a \times b$ modulo $q$.

Notice that this calculation involves three main operations: 

* integer multiplications, which we perform using a partial emulation of big integers (with only two integers: one for the least significant bits and one for the most significant ones) to avoid overflow, 

* divisions by powers of $2$ and rounding down, which we perform using right bit shifting, 

* comparisons with $q$.

## Implementation

The main ingredient of this library is the `BarrettMod` class, which stores $k$, $w-1$, and $w+1$ as parameters to perform the above calculation. It has a template parameter, `U`, which must be an unsigned integer type. (The library defines an `UnsignedInteger` concept to ensure all the required operations are implemented for the type `U`.) 

## Build

### Requirements

* Cmake version 3.22+
 
* A C++20 compiler with two's complement for unsigned integers

### Build commands.

The Makefile provides several commands to build the project, run tests, and generate the documentation:

* `make build_static` or `make`: build the static library
* `make build_dynamic`: build the dynamic library
* `make examples`: build the examples
* `make tests`: build the tests
* `make run_tests`: build and run the tests
* `make doc`: generate the documentation (requires Doxygen)
* `make open-doc`: open the documentation (works only on Linux with a default web browser set; on another operating system, just open the file `doc/html/index.html`)
* `make clean`: delete the `build` and `doc` folders (only works on systems with the `rm` command)

The output will be placed in the folders `build` (library and executables) and `doc` (documentation).

## Use

To use the library in an external program, link the latter to the static or dynamic library (or directly to the source files) and include `barrett_mut.h`.
