#define PROBLEM "https://www.luogu.com.cn/problem/P3199"

#include "../../code/graph/min_cycle_mean.hpp"

int main() {
  u32 n, m;
  std::cin >> n >> m;
  vec<edge_t<f64>> e(m);
  for (auto& [w, u, v] : e) std::cin >> u >> v >> w;
  std::cout << std::fixed << std::setprecision(8) << tifa_libs::graph::min_cycle_mean(e, n + 1) << '\n';
}

/*
考虑带权有向图 $G=(V,E)$ 以及 $w:E\rightarrow \mathbb{R}$, 每条边 $e=(i,j)$ ($i\neq j$, $i, j\in V$) 的权值定义为 $w_{i,j}$. 设 $n=|V|$. $c=(c_1,c_2,\cdots,c_k)$ ($c_i\in V$) 是 $G$ 中的一个圈当且仅当 $(c_i,c_{i+1})$ ($1\le i<k$) 和 $(c_k,c_1)$ 都在 $E$ 中. 称 $k$ 为圈 $c$ 的长度, 同时记 $c_{k+1}=c_1$, 并定义圈 $c=(c_1,c_2,\cdots,c_k)$ 的平均值为 $\mu(c)= \frac 1 k \sum\limits_{i=1}^{k} w_{c_i,c_{i+1}}$
即 $c$ 上所有边的权值的平均值. 给定图 $G=(V,E)$ 以及 $w:E\rightarrow \mathbb{R}$, 求出 $G$ 中所有圈 $c$ 的平均值的最小值 $\mu'(G)=\min_c\mu(c)$

## 输入格式
第一行两个正整数, 分别为 $n$ 和 $m$, 并用一个空格隔开. 其中 $n=|V|$, $m=|E|$ 分别表示图中有 $n$ 个点 和 $m$ 条边. 接下来 $m$ 行, 每行三个数 $i,j,w_{i,j}$, 表示有一条边 $(i,j)$ 且该边的权值为 $w_{i,j}$, 注意边权可以是实数. 输入数据保证图 $G=(V,E)$ 连通, 存在圈且有一个点能到达其他所有点
$2\leq n\le 3000$, $1\leq m\le 10000$, $|w_{i,j}| \le 10^7$, $1\leq i, j\leq n$ 且 $i\neq j$

## 输出格式
一个实数 $\mu'(G)$, 要求精确到小数点后 $8$ 位
*/

/*
4 5
1 2 5
2 3 5
3 1 5
2 4 3
4 1 3
==============
3.66666667
*/

/*
2 2
1 2 -2.9
2 1 -3.1
==============
-3.00000000
*/