---
title: interp_newton_n2
documentation_of: //src/code/math/interp_newton_n2.hpp
---

Newton's interpolation formula of given points $(x_0,y_0),(x_1,y_1),\dots,(x_{n-1},y_{n-1})$ is

$$
f(x)=f[x_0]+\sum_{i=1}^{n-1}f[x_0,x_1,\dots,x_i]\prod_{k=0}^{i-1}(x-x_i),
$$

where $f[x_0,x_1,\dots,x_i]$ is defined by

- $f[x_i]=y_i$,
- $f[x_i,x_{i+1},\dots,x_j]=\dfrac{f[x_i,x_{i+1},\dots,x_{j-1}]-f[x_{i+1},x_{i+2},\dots,x_j]}{x_i-x_j}$.
