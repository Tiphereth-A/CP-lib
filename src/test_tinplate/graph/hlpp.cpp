#define PROBLEM "https://www.luogu.com.cn/problem/P4722"

#include "../../code/graph/hlpp.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, s, t;
  std::cin >> n >> m >> s >> t;
  --s, --t;
  tifa_libs::graph::hlpp<i64> maxflow(n, s, t);
  for (u32 i = 0, u, v, w; i < m; ++i) std::cin >> u >> v >> w, --u, --v, maxflow.add(u, v, w);
  std::cout << maxflow.get();
  return 0;
}

/*
给定 $n$ 个点, $m$ 条有向边, 给定每条边的容量, 求从点 $s$ 到点 $t$ 的最大流

## 输入格式
第一行包含四个正整数 $n$, $m$, $s$, $t$, 用空格分隔, 分别表示点的个数, 有向边的个数, 源点序号, 汇点序号
接下来 $m$ 行每行包含三个正整数 $u_i$, $v_i$, $c_i$, 用空格分隔, 表示第 $i$ 条有向边从 $u_i$ 出发, 到达 $v_i$, 容量为 $c_i$
$1\leqslant n \leqslant 1200, 1\leqslant m \leqslant 120000, 1\leqslant c \leqslant 2^{31}-1$
保证答案不超过 $2^{31}-1$. 

## 输出格式
一个整数, 表示 $s$ 到 $t$ 的最大流
*/

/*
7 14 1 7
1 2 5
1 3 6
1 4 5
2 3 2
2 5 3
3 2 2
3 4 3
3 5 3
3 6 7
4 6 5
5 6 1
6 5 1
5 7 8
6 7 7
===========
14
*/

/*
10 16 1 2
1 3 2
1 4 2
5 2 2
6 2 2
3 5 1
3 6 1
4 5 1
4 6 1
1 7 2147483647
9 2 2147483647
7 8 2147483647
10 9 2147483647
8 5 2
8 6 2
3 10 2
4 10 2
=================
8
*/