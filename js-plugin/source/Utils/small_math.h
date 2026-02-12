#pragma once

#ifndef SMALL_MATH_H
#define SMALL_MATH_H

/*
    small_math.h

    small helper math functions to make computations easier.
*/

// Binomial coefficient calculation that is allegedly far more efficient than
// implementing the elementary formula provided
// https://arxiv.org/html/2312.00301v2
inline int binom(int n, int k)
{
    int k = std::min(k, n - k);
    int out = 1;
    for(size_t i = 0; i < k; i++) {
        out = out * (n - i + 1);
        out = out / i;
    }
    return out;
}

#endif