#define PROBLEM "https://www.luogu.com.cn/problem/P5367"

#include "../../code/math/cantor.hpp"

#include "../../code/math/cantor_seq2val.hpp"

void solve() {
  u32 n;
  std::cin >> n;
  vec<u32> a(n);
  for (auto& i : a) std::cin >> i;
  std::cout << tifa_libs::math::cantor_seq2val(tifa_libs::math::cantor_seq(a), 998244353) << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}

/*
求 $1\sim N$ 的一个给定全排列在所有 $1\sim N$ 全排列中的排名. 结果对 $998244353$ 取模

## 输入格式

第一行一个正整数 $N$

第二行 $N$ 个正整数, 表示 $1\sim N$ 的一种全排列

## 输出格式

一行一个非负整数, 表示答案对 $998244353$ 取模的值
*/

/*
3
2 1 3
==========
3
```
*/

/*
4
1 2 4 3
==============
2
*/