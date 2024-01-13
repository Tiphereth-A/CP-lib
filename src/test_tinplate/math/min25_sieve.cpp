#define PROBLEM "https://www.luogu.com.cn/problem/P5325"

#include "../../code/math/min25_sieve.hpp"

#include "../../code/math/mintdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/qpow.hpp"

using mintdata = tifa_libs::math::mintdata_ss<1'000'000'000 + 7>;
using mint = tifa_libs::math::mint<mintdata>;

mint f(u64 p, u64 c) {
  auto _ = tifa_libs::math::qpow(mint(p), c);
  return _ * (_ - 1);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;

  tifa_libs::math::min25_sieve<mint, f> min25(n);
  auto h1 = min25.sum_pk(1), h2 = min25.sum_pk(2);
  for (usz i = 1; i < h2.size(); ++i) h2[i] -= h1[i];
  std::cout << min25.run(h2) << '\n';
  return 0;
}

/*
定义积性函数$f(x)$, 且$f(p^k)=p^k(p^k-1)$ ($p$是一个质数) , 求

$$\sum_{i=1}^n f(i)$$

对$10^9+7$取模

## 输入格式

一行一个整数$n$

## 输出格式

一个整数表示答案
*/

/*
10
==================
263
*/

/*
1000000000
=================
710164413
```
*/