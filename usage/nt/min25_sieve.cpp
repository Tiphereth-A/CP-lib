#define PROBLEM "https://www.luogu.com.cn/problem/P5325"

#include "../../include/nt/min25_sieve.hpp"

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"
#include "../../include/math/qpow.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, 1'000'000'000 + 7>;

mint f(u64 p, u64 c) {
  auto _ = math::qpow(mint(p), c);
  return _ * (_ - 1);
}

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  math::min25_sieve<mint, f> min25(n);
  auto h1 = min25.sum_pk(1), h2 = min25.sum_pk(2);
  flt_ (u32, i, 1, (u32)h2.size()) h2[i] -= h1[i];
  std::cout << min25.run(h2) << '\n';
}

/*
定义积性函数 $f(x)$, 且 $f(p^k)=p^k(p^k-1)$ ($p$ 是质数), 求 $\sum_{i=1}^n f(i)$ 对 $10^9+7$ 取模

## 输入
一行一个整数 $n$

## 输出
一个整数表示答案
*/

/*
10
======
263
*/

/*
1000000000
=================
710164413
```
*/