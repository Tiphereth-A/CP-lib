#define PROBLEM "https://codeforces.com/gym/102028/problem/L"

#include "../../code/graph/ringcnt4.hpp"

#include "../../code/graph/ringenum3.hpp"
#include "../../code/math/mint_ss.hpp"
// clang-format off
#include "../../code/io/ios_pair.hpp"
#include "../../code/io/ios_container.hpp"
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
    vecpt<u32> edges(m);
    std::cin >> edges;
    for (auto &[u, v] : edges) --u, --v;
    tifa_libs::graph::alist g(n);
    for (auto [u, v] : edges) g.add_arc(u, v), g.add_arc(v, u);
    tifa_libs::graph::alist dg(n), dgv(n);
    flt_ (u32, u, 0, n)
      for (u32 v : g.g[u]) (std::make_pair(g.g[u].size(), u) < std::make_pair(g.g[v].size(), v) ? dg : dgv).add_arc(u, v);
    // 菊花图
    mint ans0 = 0;
    flt_ (u32, u, 0, n)
      if (g.g[u].size() >= 4) ans0 += inv24 * g.g[u].size() * (g.g[u].size() - 1) * (g.g[u].size() - 2) * (g.g[u].size() - 3);
    // 四元环
    mint ans1 = tifa_libs::graph::ringcnt4_impl_::run(dg, dgv);
    // 三元环+一条边
    mint ans2 = 0;
    u64 cnt2 = 0;
    tifa_libs::graph::ringenum3_impl_::run(dg, [&g, &ans2, &cnt2](u32 u, u32 v, u32 w) {
      ans2 += g.g[u].size() + g.g[v].size() + g.g[w].size() - 6;
      ++cnt2;
    });
    // P4+中间一点连出一条边
    mint ans3 = 0;
    flt_ (u32, u, 0, n) {
      if (g.g[u].size() < 2) continue;
      for (u32 v : g.g[u]) {
        if (g.g[v].size() < 3) continue;
        ans3 += inv2 * (g.g[u].size() - 1) * (g.g[v].size() - 1) * (g.g[v].size() - 2);
      }
    }
    ans3 -= ans2 * 2;
    // P5
    mint ans4 = 0;
    flt_ (u32, u, 0, n) {
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
皮卡德要求你计算, 从一个给定的简单无向图中以相等的概率从所有可能的方式中选择四条不同的边, 选择的边诱导的子图是连通的概率. 这里我们说图中的一组边与该组边中所有顶点组成的边为诱导子图
为了避免任何精度问题, 皮卡德将概率表示为 $p$, 边数表示为 $m$, 你应该报告值 $\left(p \cdot \binom{m}{4}\right) \bmod (10^9 + 7)$. 很容易证明 $p \cdot \binom{m}{4}$ 是一个整数

## 输入

输入包含多个测试用例, 第一行包含一个正整数 $T$, 表示测试用例的数量, 最多为 $10$
对于每个测试用例, 第一行包含两个整数 $n$ 和 $m$, 表示给定简单无向图中的顶点数和边数, 其中 $4 \leq n \leq 10^5$, $4 \leq m \leq 2 \times 10^5$
接下来的 $m$ 行描述图的所有边, 其中第 $i$ 行包含两个整数 $u$ 和 $v$, 表示第 $u$ 个顶点和第 $v$ 个顶点之间的一条边, 其中 $1 \leq u, v \leq n$ 且 $u \neq v$
保证给定的图中不包含环或多重边

## 输出

对于每个测试用例, 输出一行, 包含一个整数, 对应于值 $\left(p \cdot \binom{m}{4}\right) \bmod (10^9 + 7)$, 其中 $p$ 表示你需要计算的概率
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