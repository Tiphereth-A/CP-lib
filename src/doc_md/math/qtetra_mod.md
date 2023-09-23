---
title: Tetration with modulo
documentation_of: //src/code/math/qtetra_mod.hpp
---

Suppose $0^0=1$.

Calculate $a\uparrow\uparrow b\bmod m$, which

$$
a\uparrow\uparrow b:=\begin{cases}
    1,&n=0,\\
    a^{a\uparrow\uparrow(b-1)},&n>0.
\end{cases}
$$

## Bibliography

[yosupo06/library-checker-problems](https://github.com/yosupo06/library-checker-problems/blob/8c1ca6e7c1b4a30133aaa5a87028bc924c931f3e/math/tetration_mod/sol/correct.cpp).
