#define PROBLEM "https://www.luogu.com.cn/problem/P4897"

#include "../../code/graph/gomory_hu.hpp"

#include "../../code/graph/alistw.hpp"
#include "../../code/graph/path.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  u32 n, m;
  std::cin >> n >> m;
  vec<pt3<u32>> edges(m);
  ++n;
  for (auto& [w, u, v] : edges) std::cin >> u >> v >> w;
  auto gh_edges = tifa_libs::graph::gomory_hu(n, edges);
  u32 q;
  std::cin >> q;
  tifa_libs::graph::alistw<u32> g(n);
  for (auto&& [w, u, v] : gh_edges) g.add_arc(u, v, w), g.add_arc(v, u, w);
  std::map<ptt<u32>, u32> mp;
  for (auto&& [w, u, v] : gh_edges) mp[std::minmax(u, v)] = w;
  for (u32 i = 0, u, v; i < q; ++i) {
    std::cin >> u >> v;
    auto vs = tifa_libs::graph::path(g, u, v).value();
    u32 ans = std::numeric_limits<u32>::max();
    flt_ (u32, j, 1, (u32)vs.size()) {
      u32 from = vs[j - 1], to = vs[j];
      ans = tifa_libs::min(ans, mp[std::minmax(from, to)]);
    }
    std::cout << ans << '\n';
  }
  return 0;
}

/*
给定一个 $n$ 个点 $m$ 条边的无向连通图, 多次询问两点之间的最小割. 两点间的最小割是这样定义的：原图的每条边有一个割断它的代价, 你需要用最小的代价使得这两个点不连通

## 输入
第一行两个数 $n,m$. 接下来 $m$ 行, 每行 $3$ 个数 $u,v,w$, 表示有一条连接 $u$ 与 $v$ 的无向边, 割断它的代价为 $w$. 接下来这一行有一个整数$Q$, 表示询问次数 接下来 $Q$ 行, 每行两个数 $u,v$, 你需要求出 $u$ 与 $v$ 之间的最小割
注意：因为数据有误, 给定图的真实点数应该是 $n+1$ 个, 编号为 $0$ 到 $n$
$1\le n\leq 500,\quad 0\le m\leq 1500,\quad 0\le Q\leq 10^5,\quad 0\leq w\leq 10^4,\quad u\neq v$

## 输出
输出共 $Q$ 行, 每行一个整数对应询问的答案
*/

/*
4 5
1 2 2
2 3 2
4 2 3
4 3 1
1 3 1
3
1 4
2 4
2 3
==========
3
4
4
*/