#define PROBLEM "https://www.luogu.com.cn/problem/P6242"

#include "../../include/ds/segbeats_ca_msh.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  veci a(n);
  for (auto& x : a) std::cin >> x;
  tifa_libs::ds::segbeats_ca_msh<i32, i64> seg(a);
  for (u32 i = 0, opt, l, r; i < m; ++i) {
    std::cin >> opt >> l >> r, --l, --r;
    if (opt <= 2) {
      i32 k;
      std::cin >> k;
      if (opt == 1) seg.add(1, 0, n - 1, l, r, k);
      else seg.chmin(1, 0, n - 1, l, r, k);
    } else {
      if (opt == 3) std::cout << seg.querys(1, 0, n - 1, l, r) << '\n';
      else if (opt == 4) std::cout << seg.querymax(1, 0, n - 1, l, r) << '\n';
      else std::cout << seg.queryhismax(1, 0, n - 1, l, r) << '\n';
    }
  }
}

/*
本题是线段树维护区间最值操作与区间历史最值的模板
给出一个长度为 $n$ 的数列 $A$, 同时定义一个辅助数组 $B$, $B$ 开始与 $A$ 完全相同. 接下来进行了 $m$ 次操作, 操作有五种类型, 按以下格式给出:
- `1 l r k`: 对于所有的 $i\in[l,r]$, 将 $A_i$ 加上 $k$ ($k$ 可以为负数)
- `2 l r v`: 对于所有的 $i\in[l,r]$, 将 $A_i$ 变成 $\min(A_i,v)$
- `3 l r`: 求 $\sum_{i=l}^{r}A_i$
- `4 l r`: 对于所有的 $i\in[l,r]$, 求 $A_i$ 的最大值
- `5 l r`: 对于所有的 $i\in[l,r]$, 求 $B_i$ 的最大值
在每一次操作后, 我们都进行一次更新, 让 $B_i\gets\max(B_i,A_i)$

## 输入
第一行包含两个正整数 $n,m$, 分别表示数列 $A$ 的长度和操作次数
第二行包含 $n$ 个整数 $A_1,A_2,\cdots,A_n$, 表示数列 $A$
接下来 $m$ 行, 每行行首有一个整数 $op$, 表示操作类型; 接下来两个或三个整数表示操作参数, 格式见题目描述

## 输出
对于 $op\in\{3,4,5\}$ 的操作, 输出一行包含一个整数, 表示这个询问的答案
*/

/*
5 6
1 2 3 4 5
3 2 5
1 1 3 3
4 2 4
2 3 4 1
5 1 5
3 1 4
=============
14
6
6
11
*/