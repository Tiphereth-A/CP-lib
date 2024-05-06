#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum/"

#include "../../code/ds/link_cut_tree.hpp"

auto op(u64 a, u64 b) { return a + b; }
auto inv_op(u64 a, u64 b) { return a - b; }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vecu64 a(n);
  for (auto &x : a) x = 1;
  tifa_libs::ds::link_cut_tree<u64, op, inv_op> lct(n, a);
  flt_ (u32, i, 0, m) {
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
给你一棵有 $N$ 个顶点的树. 它的边是 $(u_i, v_i)$. 第 $i$ 个顶点上有一个值 $a_i$
处理 $Q$ 个查询. 保证每次查询后的图是一棵树
- 0 $u$ $v$ $w$ $x$: 删除边 $(u, v)$ 并添加边 $(w, x)$
- 1 $p$ $x$: $a_p \gets a_p + x$
- 2 $v$ $p$: 对于边 $(v, p)$, 其中 $p$ 被认为是父节点, 输出 $v$ 子树中所有顶点权重的总和

## 输入
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
=======================
10011
110011
110011
101111
*/