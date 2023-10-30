#define PROBLEM "https://www.luogu.com.cn/problem/P5396"

#include "../../code/comb/stirling2_col_gen.hpp"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polydata_s32.hpp"

using mint = tifa_libs::math::mint_s30<167772161>;
using polyd = tifa_libs::math::polydata_s32<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  auto ans = tifa_libs::math::stirling2_col_gen<polyd>(n, k);
  for (usz i = 0; i <= n; ++i) std::cout << ans[i] << " \n"[i == n];
  return 0;
}

/*
第二类斯特林数$\begin{Bmatrix} n \\m \end{Bmatrix}$表示把$n$个**不同**元素划分成$m$个**相同**的集合（不能有空集）的方案数。

给定$n,k$，对于所有的整数$i\in[0,n]$，你要求出$\begin{Bmatrix} i \\k \end{Bmatrix}$。

由于答案会非常大，所以你的输出需要对$167772161$（$2^{25}\times 5+1$，是一个质数）取模。
*/

/*
3 2
===========
0 0 1 3
*/