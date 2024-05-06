#define PROBLEM "https://www.luogu.com.cn/problem/P8436"

#include "../../code/graph/e_bcc.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  struct EW {
    u32 to, inv;
  };
  vvec<EW> e(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    if (u == v) continue;
    --u, --v;
    u32 tem1 = u32(e[u].size()), tem2 = u32(e[v].size());
    e[u].push_back({v, tem2});
    e[v].push_back({u, tem1});
  }
  tifa_libs::graph::e_bcc<EW> bcc(e);
  std::cout << bcc.id << '\n';
  for (u32 i = 0; i < bcc.id; ++i) {
    std::cout << bcc.belongs[i].size() << ' ';
    for (auto x : bcc.belongs[i])
      std::cout << x + 1 << ' ';
    std::cout << '\n';
  }
  return 0;
}

/*
对于一个 $n$ 个节点 $m$ 条无向边的图, 请输出其边双连通分量的个数, 并且输出每个边双连通分量

## 输入
第一行, 两个整数 $n$ 和 $m$
接下来 $m$ 行, 每行两个整数 $u, v$, 表示一条无向边
$1 \le n \le 5 \times10 ^5$, $1 \le m \le 2 \times 10^6$

## 输出
第一行一个整数 $x$ 表示边双连通分量的个数
接下来的 $x$ 行, 每行第一个数 $a$ 表示该分量结点个数, 然后 $a$ 个数, 描述一个边双连通分量
你可以以任意顺序输出边双连通分量与边双连通分量内的结点

## 提示
样例四解释参见 PDF
相同颜色的点为同一个连通分量
*/

/*
5 8
1 3
2 4
4 3
1 2
4 5
5 1
2 4
1 1
================
1
5 1 5 4 2 3
*/

/*
5 3
1 2
2 3
1 3
===========
3
3 1 3 2
1 4
1 5
*/

/*
6 5
1 3
2 4
1 2
4 6
2 3
==========
4
3 1 2 3
1 4
1 5
1 6
*/

/*
7 8
1 3
2 4
3 5
2 5
6 4
2 5
6 3
2 7
===============
3
1 1
5 2 5 3 6 4
1 7
*/