#define PROBLEM "https://codeforces.com/gym/102028/problem/L"

#include "../../code/graph/ringcnt4.hpp"

#include "../../code/graph/ringenum3.hpp"
#include "../../code/math/mint_ss.hpp"
// clang-format off
#include "../../code/util/ios_pair.hpp"
#include "../../code/util/ios_container.hpp"
// clang-format on

using mint = tifa_libs::math::mint_ss<1'000'000'000 + 7>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 T;
  std::cin >> T;
  const mint inv24 = mint(24).inv(), inv2 = mint(2).inv();
  while (T--) {
    u32 n, m;
    std::cin >> n >> m;
    vec<ptt<u32>> edges(m);
    std::cin >> edges;
    for (auto &[u, v] : edges) --u, --v;
    tifa_libs::graph::alist g(n);
    for (auto [u, v] : edges) g.add_arc(u, v), g.add_arc(v, u);
    tifa_libs::graph::alist dg(n), dgv(n);
    for (u32 u = 0; u < n; ++u)
      for (u32 v : g.g[u]) (std::make_pair(g.g[u].size(), u) < std::make_pair(g.g[v].size(), v) ? dg : dgv).add_arc(u, v);
    // 菊花图
    mint ans0 = 0;
    for (u32 u = 0; u < n; ++u)
      if (g.g[u].size() >= 4) ans0 += inv24 * g.g[u].size() * (g.g[u].size() - 1) * (g.g[u].size() - 2) * (g.g[u].size() - 3);
    // 四元环
    mint ans1 = tifa_libs::graph::ringcnt4_impl_::run_(dg, dgv);
    // 三元环+一条边
    mint ans2 = 0;
    u64 cnt2 = 0;
    tifa_libs::graph::ringenum3_impl_::run(dg, [&g, &ans2, &cnt2](u32 u, u32 v, u32 w) {
      ans2 += g.g[u].size() + g.g[v].size() + g.g[w].size() - 6;
      ++cnt2;
    });
    // P4+中间一点连出一条边
    mint ans3 = 0;
    for (u32 u = 0; u < n; ++u) {
      if (g.g[u].size() < 2) continue;
      for (u32 v : g.g[u]) {
        if (g.g[v].size() < 3) continue;
        ans3 += inv2 * (g.g[u].size() - 1) * (g.g[v].size() - 1) * (g.g[v].size() - 2);
      }
    }
    ans3 -= ans2 * 2;
    // P5
    mint ans4 = 0;
    for (u32 u = 0; u < n; ++u) {
      mint _ = 0;
      for (u32 v : g.g[u]) {
        ans4 += _ * (g.g[v].size() - 1);
        _ += g.g[v].size() - 1;
      }
    }
    ans4 -= 2 * ans2 + 4 * ans1 + 3 * cnt2;
    // total
    std::cout << ans0 + ans1 + ans2 + ans3 + ans4 << '\n';
  }
  return 0;
}

/*
An algorithm master in graph theory would never endure any disconnected subgraph.

An esthetician would only consider edge-induced subgraphs as necessary subgraphs.

An OCD patient would always choose a subgraph from a given simple undirected graph randomly.

Those are why Picard asks you to calculate, for choosing four different edges from a given simple undirected graph with equal probability among all possible ways, the probability that the edge-induced subgraph formed by chosen edges is connected. Here we say a subset of edges in the graph together with all vertices that are endpoints of edges in the subset form an edge-induced subgraph.

To avoid any precision issue, Picard denotes the probability as $p$ and the number of edges as $m$, and you should report the value $\left(p \cdot \binom{m}{4}\right) \bmod (10^9 + 7)$. It is easy to show that $p \cdot \binom{m}{4}$ is an integer.

**Input**

The input contains several test cases, and the first line contains a positive integer $T$ indicating the number of test cases which is up to $10$.

For each test case, the first line contains two integers $n$ and $m$ indicating the numbers of vertices and edges in the given simple undirected graph respectively, where $4 \leq n \leq 10^5$ and $4 \leq m \leq 2 \times 10^5$.

The following $m$ lines describe all edges of the graph, the $i$\-th line of which contains two integers $u$ and $v$ which represent an edge between the $u$\-th vertex and the $v$\-th vertex, where $1 \leq u, v \leq n$ and $u \neq v$.

We guarantee that the given graph contains no loops or multiple edges.

**Output**

For each test case, output a line containing an integer corresponding to the value $\left(p \cdot \binom{m}{4}\right) \bmod (10^9 + 7)$, where $p$ indicates the probability which you are asked to calculate.
*/

/*
2
4 4
1 2
2 3
3 4
4 1
4 6
1 2
1 3
1 4
2 3
2 4
3 4
==============
1
15
*/