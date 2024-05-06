#define PROBLEM "https://www.luogu.com.cn/problem/P6192"

#include "../../code/graph/steiner_tree.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, k;
  std::cin >> n >> m >> k;
  tifa_libs::graph::alistw<u32> e(n);
  for (u32 i = 0, u, v, w; i < m; ++i) std::cin >> u >> v >> w, --u, --v, e.add_arc(u, v, w), e.add_arc(v, u, w);
  vecu a(k);
  for (auto& x : a) std::cin >> x, --x;
  tifa_libs::graph::steiner_tree st(e, a);
  std::cout << st.val();
  return 0;
}

/*
给定一个包含 $n$ 个结点和 $m$ 条带权边的无向连通图 $G=(V,E)$.
再给定包含 $k$ 个结点的点集 $S$, 选出 $G$ 的子图 $G'=(V',E')$, 使得:
1. $S\subseteq V'$;
2. $G'$ 为连通图;
3. $E'$ 中所有边的权值和最小.
你只需要求出 $E'$ 中所有边的权值和.

## 输入
第一行: 三个整数 $n,m,k$, 表示 $G$ 的结点数,边数和 $S$ 的大小.
接下来 $m$ 行: 每行三个整数 $u,v,w$, 表示编号为 $u,v$ 的点之间有一条权值为 $w$ 的无向边.
接下来一行: $k$ 个互不相同的正整数, 表示 $S$ 的元素.
$1\leq n\leq 100,\ \ 1\leq m\leq 500,\ \ 1\leq k\leq 10,\ \ 1\leq u,v\leq n,\ \ 1\leq w\leq 10^6$.
保证给出的无向图连通, 但可能存在重边和自环.

## 输出
第一行: 一个整数, 表示 $E'$ 中边权和的最小值.

## 样例解释
样例中给出的图如下图所示, 红色点为 $S$ 中的元素, 红色边为 $E'$ 的元素, 此时 $E'$ 中所有边的权值和为 $2+2+3+4=11$, 达到最小值.
样例图片参见 PDF
*/

/*
7 7 4
1 2 3
2 3 2
4 3 9
2 6 2
4 5 3
6 5 2
7 6 4
2 4 7 5
=============
11
*/