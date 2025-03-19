#define PROBLEM "https://codeforces.com/gym/103446/problem/H"

#include "../../include/graph/kruskal_re_tree.hpp"

#include "../../include/tree/dfs_info.hpp"
#include "../../include/tree/tree_sumvw.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, q;
  std::cin >> n >> m >> q;
  vecu nw(n);
  for (auto& x : nw) std::cin >> x;
  vec<edge_tu> e(m);
  for (auto& [w, u, v] : e) std::cin >> u >> v >> w, --u, --v;
  std::ranges::sort(e);
  auto [tr, ew] = tifa_libs::graph::kruskal_re_tree(e, n);
  n = (u32)tr.g.size();
  tifa_libs::graph::tree_dfs_info<tifa_libs::graph::tree, tifa_libs::graph::tdi_go> info(tr);
  nw.resize(n);
  auto sum_node_w = tifa_libs::graph::tree_sumvw(tr, nw);
  while (q--) {
    u32 x, k;
    std::cin >> x >> k, --x;
    u64 ans = k + sum_node_w[x];
    while (x != tr.root) {
      u32 tem = x;
      for (u32 i = 20; ~i; --i)
        if (info.go[x][i] < n && ew[info.go[x][i]] <= ans) x = info.go[x][i];
      if (x == tem) break;
      ans = k + sum_node_w[x];
    }
    std::cout << ans << '\n';
  }
  return 0;
}

/*
生活就是一场游戏
世界可以看作是一个有 $n$ 个城市和 $m$ 条城市之间的无向连接图. 现在, 你作为生活游戏玩家, 要在这个世界图上进行生活游戏
最初, 你在第 $x$ 个城市, 并且拥有 $k$ 点社交能力. 你可以通过生活和工作来获得社交能力点. 具体来说, 你可以在第 $i$ 个城市生活和工作获得 $a_i$ 点社交能力. 但在这个问题中, 你不能在同一个城市重复获得社交能力点, 所以你想要环游世界并获得更多的社交能力点. 然而, 路途并不容易. 具体来说, 对于第 $i$ 条道路, 有一个能力门槛 $w_i$, 你必须至少拥有 $w_i$ 点社交能力才能通过这条道路. 此外, 当通过道路时, 你的社交能力点不会减少, 但如果你想要通过第 $i$ 条道路, 你只需至少有 $w_i$ 点社交能力
所以你可以看到, 生活游戏就是不断地生活, 工作和旅行. 有 $q$ 个游戏存档. 对于每个游戏存档, 给定初始城市和社交能力点, 并且玩家还没有在任何城市生活或工作. 现在, 你, 真实的生活游戏玩家, 需要确定你在游戏结束时可能拥有的最大社交能力点数, 并输出给定游戏存档的结果

## 输入
第一行包含三个整数 $n,m,q,(1\le n,m,q \le 10^5)$, 分别表示城市数量, 道路数量和游戏存档数量
第二行包含 $n$ 个整数 $a_1, a_2, \cdots, a_n,(1\le a_i \le 10^4)$, 表示每个城市的社交能力点奖励
接下来的 $m$ 行, 每行包含三个整数 $u, v, w,(1\le u < v \le n, 1\le w \le 10^9)$, 表示城市 $u,v$ 之间由能力门槛为 $w$ 的道路双向连接
接下来的 $q$ 行, 每行包含两个整数 $x, k,(1\le x \le n, 1\le k \le 10^9)$, 表示游戏存档的初始城市和社交能力点

## 输出
对于每个游戏存档, 输出一行, 包含一个整数, 表示你可能拥有的最大社交能力点数
*/

/*
8 10 2
3 1 4 1 5 9 2 6
1 2 7
1 3 11
2 3 13
3 4 1
3 6 31415926
4 5 27182818
5 6 1
5 7 23333
5 8 55555
7 8 37
1 7
8 30
=====================
16
36
*/