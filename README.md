# Barrett Multiplication

This is a simple example of C++ code to compute the product of two integers modulo a third one using only ‘fast’ operations (right bit shifting, addition, subtraction, multiplication, and comparison). 

## A bit of theory

### A first scheme

Let $q$ be a positive integer larger than $1$. Let $w$ be the logarithm of $q$ in base $2$, rounded up. Let $a$ and $b$ be two non-negative integers smaller than $2^w$. We want to compute the product of $a$ and $b$ modulo $q$, *i.e.*, the remainder of the Euclidean division of $a \times b$ by $q$.

We proceed as follows. First, we pre-compute $w$ and the integer $k$  given by $k = \lfloor 2^{2 w} / q \rfloor$. We then compute the following quantities: 

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

**NB:** This argument still works with $a \times b$ replaced by any non-negative integer smaller than $2^{2w}$. 

### A variant

If the point of the modular reduction is to prevent the range from growing indefinitely when doing successive calculations, one can do one fewer comparison at the cost of a larger exponent. Let $w'$ be an integer strictly larger than $w$ and $k' = \lfloor 2^{2w'} / q \rfloor$. Let $x$ be a natural integer no larger than $2^{w'}$. We want to find an integer $y$ such that $y \equiv x \; \mathrm{mod} \; q$ and $0 \leq y < 2^{w'}$. 

Let $x_2 = \lfloor x / 2^{w'-1} \rfloor$ and $x_3 = \lfloor (x_2 \times k' ) / 2^{w'+1} \rfloor$.
Let $z = x - q \times x_3$ and $y = z$ if $z < 2^w$ or $y = z - q$ otherwise. We claim that $y$ satisfies the above properties. 

**Proof:** First note that $z \equiv x \; \mathrm{mod} \; q$ and $y \equiv x \; \mathrm{mod} \; q$ by construction. Let us show that $y$ is in the right range. 

We have: 
$$
\frac{x_2 \times k'}{2^{w'+1}} - 1 
< x_3 
\leq \frac{x_2 \times k'}{2^{w'+1}} ,
$$

$$
\frac{x}{2^{w'-1}} - 1
< x_2
\leq \frac{x}{2^{w'-1}},
$$

and
$$
\frac{2^{2 w'}}{q} - 1
< k'
\leq \frac{2^{2 w'}}{q}.
$$
So, 
$$
\frac{x}{q} - \frac{2^{w'-1}}{q} - \frac{x}{2^{2 w'}} + \frac{1}{2^{w'+1}} - 1
< x_3
\leq \frac{x}{q} .
$$
From this double inequality, we immediately get:
$$
0 \leq 
x - q \times x_3
< 2^{w'-1} + \frac{x \times q}{2^{2 w'}} + q - \frac{q}{2^{w'+1}}.
$$
Since $x \leq 2^{2 w'}$,  this gives:
$$
0 \leq 
z
< 2^{w'-1} + 2 \times q .
$$
Since $w' > w$, $w' \geq w+1$; since $q \leq 2^w$, we thus have $q \leq 2^{w'-1}$. the above double inequality thus gives: 
$$
0 \leq z
< 2^{w'} + q.
$$
If $z < 2^{w'}$, $z$ satisfies the desired properties, and thus so does $y$ (since $y = z$ in this case). Otherwise, $z > q$ and $y = z - q$, so $y > 0$, and, from the second inequality above, $y < 2^{w'}$. the integer $y$ thus still satisfies the desired properties. $\square$



**NB:** Notice that this scheme is optimal, in the sense that we can't (in general) choose $w' = w$. As a counter-example, let us choose $q = 113$ and $x = 11772$. We then have $x = a \times b$ with $a = 108$ and $b = 109$. Then, $w = 7$ and $2^w = 128$. So, $a < 2^w$ and $b < 2^w$ (so $x < 2^{2w}$). We have $k = \lfloor 128^2 / q \rfloor = 144$. Let us try  to follow the above procedure with $w' = w$. then, $x_2 = \lfloor 11772 / 2^6 \rfloor = \lfloor 11772 / 64 \rfloor = 183$ and $x_3 = \lfloor (183 \times 144 ) / 2^8 \rfloor = \lfloor (183 \times 144 ) / 2^8 \rfloor = 102$. So, $z = 11772 - 113 \times 102 = 246 = 2^w +q + 5$. We thus get $z > 2^w + q$, so neither $z$ nor $z-q$ is in the range $[\![0, 2^w]\!]$.

### A variant using larger numbers

The above algorithm only involves numbers in the range $[\![0, 2^{2w}-1]\!]$. It can be simplified at the cost of intermediate results only being constrained to the larger range $[\![0, 2^{3w}-1]\!]$ as follows. 

Let us compute the following quantities: 

$$
x_1 = a \times b
$$

$$
x_2 = \lfloor (x_1 \times k) / 2^{2w} \rfloor
$$

$$
c = x_1 - x_2 \times q.
$$

Obviously, $c \equiv a \times b \; \mathrm{mod} \; q$. Moreover, we have

$$
\frac{x_1 \times k}{2^{2w}} - 1 < x_2 \leq \frac{x_1 \times k}{2^{2w}}
$$

and

$$
\frac{2^{2 w}}{q} - 1 < k \leq \frac{2^{2 w}}{q},
$$

so

$$
\frac{x_1}{q} - \frac{x_1}{2^{2w}} - 1 < x_2 \leq \frac{x_1}{q},
$$

$$
\frac{x_1 \times q}{2^{2w}} + q > x_1 - q \times x_2 \geq 0.
$$

Since $a, b < q \leq 2^w$, $x_1 < 2^{2w}$. So, 

$$
0 \leq x_1 - q \times x_2 < 2 q.
$$

So, either $c$, or $c - q$ is in the range $[0, q)$, and thus equal to the reduction of $a \times b$ modulo $q$.

### An alternative: Shoup multiplication

**Problem:** Let $q$ be a positive integer and $w$ a fixed integer in $[\![0, q[\![$. Let $f$ be the function from $[\![0, q[\![$ to itself defined by: for each element $x$ of $[\![0, q[\![$, $f(x) = (w \times x) \; \mathrm{mod} \; q$. 

**Claim:** Let $\beta$ be a positive integer such that $\beta \geq q$. (One generally chooses $\beta$ as a power of $2$ for performance.) We define $w'$ by: $w' = \lfloor w \beta  / q \rfloor$. For each element $x$ of $\mathbb{N}$, we define $g(x)$ by:
$$
g(x) = w \, x - \left\lfloor \frac{w' \, x}{\beta} \right\rfloor q .
$$
Then, for each positive integer $x$ strictly smaller than $q$, $f(x) = g(x)$ if $g(x) < q$ or $f(x) = g(x) - q$ otherwise.

Moreover, if $\beta \geq 2 q$, then $g(x) < 2 q$ for all $x$ in $[\![0, 2 q]\!]$.

If $\beta$ is a power of $2$, this calculation require one integer multiplication, one bit shift, one comparison, and one or two subtractions. It may be more efficient than Barrett reduction if $w'$ is pre-computed.

**Proof:** By construction, the result is equal to $w \, x$ modulo $q$. Let us show that it is in the right range.

We have: 
$$
\frac{w' \, x}{\beta} q - q < \left\lfloor \frac{w' \, x}{\beta} \right\rfloor q \leq \frac{w' \, x}{\beta} q.
$$
Since 
$$
\frac{w \, \beta}{q} - 1 < w' \leq \frac{w \, \beta}{q},
$$
this gives: 
$$
w \, x - \frac{x}{\beta} q - q < \left\lfloor \frac{w' \, x}{\beta} \right\rfloor q \leq w \, x.
$$
If $x < q$, and $q < \beta$, $x < \beta$, so 
$$
w \, x - 2 \, q < \left\lfloor \frac{w' \, x}{\beta} \right\rfloor q \leq w \, x
$$
and
$$
0 \leq g(x) < 2 \, q.
$$
If $x \leq 2 \, q$ and $\beta \geq 2 q$, we have $x \leq \beta$, so 
$$
w \, x - 2 \, q < \left\lfloor \frac{w' \, x}{\beta} \right\rfloor q \leq w \, x
$$
again, and
$$
0 \leq g(x) < 2 \, q.
$$


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
