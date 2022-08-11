# Barrett Multiplication

This is a simple example of C++ code to compute the product of two integers modulo a third one. 

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

Notice that this calculation involves two main operations: 

* integer multiplications, which we perform using a partial emulation of big integers (with only two integers: one for the least significant bits and one for the most significant ones) to avoid overflow, 

* divisions by powers of $2$ and rounding down, which we perform using right bit shifting.
