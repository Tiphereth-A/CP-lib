#define PROBLEM "https://www.luogu.com.cn/problem/P3376"

#include "../../include/graph/dinic.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, s, t;
  std::cin >> n >> m >> s >> t, --s, --t;
  graph::dinic maxflow(n);
  for (u32 i = 0, u, v, w; i < m; ++i) std::cin >> u >> v >> w, --u, --v, maxflow.add(u, v, w);
  std::cout << maxflow.get(s, t);
}

/*
给出一个网络图, 以及其源点和汇点, 求出其网络最大流

## 输入
第一行包含四个正整数 $n,m,s,t$, 分别表示点的个数, 有向边的个数, 源点序号, 汇点序号
接下来 $m$ 行每行包含三个正整数 $u_i,v_i,w_i$, 表示第 $i$ 条有向边从 $u_i$ 出发, 到达 $v_i$, 边权为 $w_i$ (即该边最大流量为 $w_i$)
$1 \leq n\leq200$, $1 \leq m\leq 5000$, $0 \leq w< 2^{31}$

## 输出
一行, 包含一个正整数, 即为该网络的最大流

## 提示
样例图片参见 PDF
题目中存在 $3$ 条路径:
- $4\to 2\to 3$, 该路线可通过 $20$ 的流量
- $4\to 3$, 可通过 $20$ 的流量
- $4\to 2\to 1\to 3$, 可通过 $10$ 的流量 (边 $4\to 2$ 之前已经耗费了 $20$ 的流量)
故流量总计 $20+20+10=50$. 输出 $50$
*/

/*
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 30
=========
50
*/