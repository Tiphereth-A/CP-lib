---
title: Do something over quotients
documentation_of: //src/code/math/do_quot.hpp
---

Enumerate arbitary quotients of $\lfloor n/l\rfloor,~\forall 1\leq l\leq n$ in descending order, and run `f(l, r, q)`, which $\lfloor n/i\rfloor=q,~\forall l\leq i\leq r$.

For example, you can use

```cpp
u64 ans = 0;
do_quot(100, [&ans](u64 l, u64 r, u64 q) { ans += q; })
```

to calculate

$$
\sum_{i\in S}i,
$$

which $S=\{\lfloor 100/i \rfloor: 1\leq i\leq 100\}$

you can also use

```cpp
u64 ans = 0;
do_quot(100, [&ans](u64 l, u64 r, u64 q) { ans += (r - l + 1) * q; })
```

to calculate

$$
\sum_{i=1}^{100}\left\lfloor\frac{100}{i}\right\rfloor.
$$
