#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum/"

#include "../../code/ds/link_cut_tree.hpp"

auto op(u64 a, u64 b) { return a + b; }
auto inv_op(u64 a, u64 b) { return a - b; }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<u64> a(n);
  for (auto &x : a) x = 1;
  tifa_libs::ds::link_cut_tree<u64, op, inv_op> lct(n, a);
  for (u32 i = 0; i < m; ++i) {
    char opt;
    u32 u, v;
    std::cin >> opt >> u >> v;
    --u, --v;
    if (opt == 'A') lct.link(u, v);
    else {
      auto ret = lct.query_subtree(u, v);
      std::cout << ret.first * ret.second << '\n';
    }
  }
  return 0;
}

/*
You are given a tree with $N$ vertices. Its edges are $(u_i, v_i)$. Its $i$-th vertex has a value $a_i$ written on it.

Process $Q$ queries. It is guaranteed that the graph is a tree after each query.

- `0 $u$ $v$ $w$ $x$`: Remove an edge $(u, v)$ and add an edge $(w, x)$.
- `1 $p$ $x$`: $a_p \gets a_p + x$
- `2 $v$ $p$`: For an edge $(v, p)$ where $p$ is considered the parent, output the sum of weights of all vertices in the subtree of $v$.

## input

$N$ $Q$
$a_0$ $a_1$ ... $a_{N - 1}$
$u_0$ $v_0$
$u_1$ $v_1$
:
$u_{N - 2}$ $v_{N - 2}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
*/

/*
5 7
1 10 100 1000 10000
0 1
1 2
2 3
1 4
2 1 2
1 1 100000
2 1 2
0 1 2 2 0
2 0 2
0 2 3 3 1
2 1 4
============
10011
110011
110011
101111
*/