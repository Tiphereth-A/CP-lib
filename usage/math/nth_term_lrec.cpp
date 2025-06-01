#define PROBLEM "https://www.luogu.com.cn/problem/P4723"

#include "../../include/math/nth_term_lrec.hpp"

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"
#include "../../include/poly/polyntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, 998244353>;
using poly = math::polyntt<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  vec<mint> f(k + 1), a(k);
  f[0] = 1;
  for (u32 i = 1; i <= k; ++i) {
    mint x;
    std::cin >> x, f[i] = -x;
  }
  for (auto &i : a) std::cin >> i;
  std::cout << math::nth_term_lrec<poly>(n, a, f) << '\n';
}

/*
求一个满足 $k$ 阶齐次线性递推数列 ${a_i}$ 的第 $n$ 项, 即 $a_n=\sum\limits_{i=1}^{k}f_i \times a_{n-i}$

## 输入格式
第一行两个数 $n$,$k$, 如题面所述
第二行 $k$ 个数, 表示 $f_1 \ f_2 \ \cdots \ f_k$
第三行 $k$ 个数, 表示 $a_0 \ a_1 \ \cdots \ a_{k-1}$
$N = 10^{9}, K = 32000$, 保证读入的数字均为 $[-10^9,10^9]$ 内的整数

## 输出格式
一个数, 表示 $a_n \bmod 998244353$ 的值
*/

/*
6 4
3 -1 0 4
-2 3 1 5
===========
73
*/