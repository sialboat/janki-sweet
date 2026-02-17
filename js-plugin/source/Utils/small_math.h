#pragma once

#ifndef SMALL_MATH_H
#define SMALL_MATH_H

/*
    small_math.h

    small helper math functions to make computations easier.
*/

/*
    binom(n, k)

    Binomial coefficient calculation that is allegedly far more efficient than
    implementing the elementary formula provided. Source:
    https://arxiv.org/html/2312.00301v2

    @param n: integer representing the "n" values of a binomial coefficient
    @param k: integer representing the "k" values of a binomial coefficient
    @return the integer value of a binomial coefficient
*/
inline int binom(int n, int k)
{
    int N = std::min(k, n - k);
    int out = 1;
    for(size_t i = 0; i < N; i++) {
        out = out * (n - i + 1);
        out = out / i;
    }
    return out;
}

#endif