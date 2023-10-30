#define PROBLEM "https://www.luogu.com.cn/problem/P3372"

#include "../../code/ds/fenwick.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::ds::fenwick<i64> tr(n + 1), tri(n + 1);
  for (i64 i = 1, a, b = 0; i <= n; ++i) {
    std::cin >> a;
    tr.add(i, b = a - b);
    tri.add(i, (i - 1) * b);
    b = a;
  }
  for (i64 i = 0, op, l, r, k; i < m; ++i) {
    std::cin >> op >> l >> r;
    if (op == 1) {
      std::cin >> k;
      tr.add(l, k);
      tr.add(r + 1, -k);
      tri.add(l, (l - 1) * k);
      tri.add(r + 1, r * -k);
    } else std::cout << (r * tr.sum(r) - (l - 1) * tr.sum(l - 1)) - (tri.sum(r) - tri.sum(l - 1)) << '\n';
  }
  return 0;
}

/*
已知一个数列，你需要进行下面两种操作：

1. 将某区间每一个数加上 $k$。
2. 求出某区间每一个数的和。

## 输入格式

第一行包含两个整数 $n, m$，分别表示该数列数字的个数和操作的总个数。

第二行包含 $n$ 个用空格分隔的整数，其中第 $i$ 个数字表示数列第 $i$ 项的初始值。

接下来 $m$ 行每行包含 $3$ 或 $4$ 个整数，表示一个操作，具体如下：

1. `1 x y k`：将区间 $[x, y]$ 内每个数加上 $k$。
2. `2 x y`：输出区间 $[x, y]$ 内每个数的和。
*/

/*
5 5
1 5 4 2 3
2 2 4
1 2 3 2
2 3 4
1 1 5 1
2 1 4
==========
11
8
20
*/