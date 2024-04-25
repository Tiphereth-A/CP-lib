#define PROBLEM "https://vjudge.net/problem/UVA-11525"

#include "../../code/edh/cantor_inv.hpp"

void solve() {
  u32 n;
  std::cin >> n;
  vecu a(n);
  for (auto& i : a) std::cin >> i;
  auto p = tifa_libs::cantor_inv_seq(a);
  flt_ (u32, i, 0, n) std::cout << p[i] << " \n"[i == n - 1];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}

/*
给定 $N$ 和 $K$, 找出整数 1 到 $K$ 的排列中第 $N$ 个排列, $N$ 从 $0$ 开始计数. 由于 N 非常大, N 将由一系列 $K$ 个非负整数 $S_1,S_2,\dots,S_k$ 表示. 通过这些整数序列, 可以用以下表达式计算出 $N$
$\sum_{i=1}^K S_i*(K-i)!$

## 输入

第一行包含一个整数 $T~(\le 10)$, 表示测试用例的数量. 每个测试用例由 2 行组成. 第一行包含一个整数 $K~(1 \le K \le 50000)$. 接下来的一行包含 $K$ 个整数 $S_1,S_2,\dots,S_k.~(0 \le Si \le K - i)$

## 输出

对于每个测试用例，输出包含整数 $1$ 到 $K$ 的第 $N$ 个排列. 用单个空格分隔
*/

/*
4
3
2 1 0
3
1 0 0
4
2 1 1 0
4
1 2 1 0
==========
3 2 1
2 1 3
3 2 4 1
2 4 3 1
*/