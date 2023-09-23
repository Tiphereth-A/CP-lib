---
title: Linear seive
documentation_of: //src/code/math/linear_seive.hpp
---

Seive primes in $[2,n)$

## Input

- `n`: range;
- `cb_prime`: callback function when enumerated a prime `p`, will be called as `cb_prime(u32 p)`;
- `cb_coprime`: callback function when `i` and `j` are coprime, will be called as `cb_coprime(u32 i, u32 j)`;
- `cb_now_coprime`: callback function when `i` and `j` are not coprime, will be called as `cb_now_coprime(u32 i, u32 j)`.
