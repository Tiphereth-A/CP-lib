#define PROBLEM "https://www.luogu.com.cn/problem/P10216"

#include "../../include/lalg/pfaffian_mat.hpp"

#include "../../include/lalg/mat.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_ms.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1'000'000'007;

using mint = math::mint<math::mint_ms, MOD>;
using mat = math::matrix<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  flt_ (u32, i, 0, n - 1)
    flt_ (u32, j, i + 1, n) std::cin >> a(i, j);
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  std::cout << math::pfaffian(a, is_0) << '\n';
}

/*
给定偶数 $n$ 与反对称矩阵 $\mathbf{A}=(a_{i,j})_{1\le i<j\le n}$, 求 $\textup{pf}(\mathbf{A})$ 对 $10^9+7$ 取模的结果

## 输入格式
第一行一个正整数 $n$, 保证 $n$ 是偶数
接下来 $n-1$ 行, 第 $i$ 行有 $n-i$ 个非负整数, 其中第 $j$ 个整数表示 $a_{i,i+j}$
$2\leq n\le 500$, $0\le a_{i,j}<10^9+7$

## 输出格式
一行一个非负整数, 表示答案
*/

/*
4
1 2 3
4 5
6
========
8
*/
