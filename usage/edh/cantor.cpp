#define PROBLEM "https://www.luogu.com.cn/problem/P5367"

#include "../../include/edh/cantor.hpp"

#include "../../include/edh/cantor_seq2val.hpp"

using namespace tifa_libs;
void solve() {
  u32 n;
  std::cin >> n;
  vecu a(n);
  for (auto& i : a) std::cin >> i;
  std::cout << cantor_seq2val(cantor_seq(a), 998244353) << '\n';
}

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  solve();
}

/*
求 $1\sim N$ 的一个给定全排列在所有 $1\sim N$ 全排列中的排名. 结果对 $998244353$ 取模

## 输入
第一行一个正整数 $N$
第二行 $N$ 个正整数, 表示 $1\sim N$ 的一种全排列

## 输出
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