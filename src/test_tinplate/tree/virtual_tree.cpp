#define PROBLEM "https://www.luogu.com.cn/problem/P2495"

#include "../../code/tree/virtual_tree.hpp"

#include "../../code/tree/tree.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu sign(n), min_(n);
  tifa_libs::graph::tree tr(n);
  {
    using Tw = u32;
    tifa_libs::graph::treew<Tw> trw(n);
    for (u32 i = 1, u, v, w; i < n; ++i) std::cin >> u >> v >> w, --u, --v, tr.add_arc(u, v), tr.add_arc(v, u), trw.add_arc(u, v, w), trw.add_arc(v, u, w);
    auto dfs = [&](auto&& dfs, u32 u, u32 fa, u32 min__) -> void {
      min_[u] = min__;
      for (auto [to, w] : trw.g[u])
        if (to != fa) dfs(dfs, to, u, tifa_libs::min(min__, w));
    };
    dfs(dfs, 0, 0, INT32_MAX);
  }
  tifa_libs::graph::virtual_tree::tree_info_t info(tr);
  tifa_libs::graph::virtual_tree vt(tr, info);
  u32 m, k;
  std::cin >> m;
  flt_ (u32, i, 0, m) {
    std::cin >> k;
    vecu a(k);
    for (auto& x : a) std::cin >> x, --x, sign[x] = 1;
    vt.build(a);
    auto dp = [&](auto&& dp, u32 u) -> u64 {
      if (sign[u]) return min_[u];
      u64 ret = 0;
      for (u32 to : vt.vt.g[u]) ret += dp(dp, to);
      return u ? tifa_libs::min(u64(min_[u]), ret) : ret;
    };
    std::cout << dp(dp, 0) << '\n';
    flt_ (u32, i, 0, k) sign[a[i]] = 0;
  }
}

/*
在一场战争中, 战场由 $n$ 个岛屿和 $n-1$ 个桥梁组成, 保证每两个岛屿间有且仅有一条路径可达. 现在, 我军已经侦查到敌军的总部在编号为 $1$ 的岛屿, 而且他们已经没有足够多的能源维系战斗, 我军胜利在望. 已知在其他 $k$ 个岛屿上有丰富能源, 为了防止敌军获取能源, 我军的任务是炸毁一些桥梁, 使得敌军不能到达任何能源丰富的岛屿. 由于不同桥梁的材质和结构不同, 所以炸毁不同的桥梁有不同的代价, 我军希望在满足目标的同时使得总代价最小
侦查部门还发现, 敌军有一台神秘机器. 即使我军切断所有能源之后, 他们也可以用那台机器. 机器产生的效果不仅仅会修复所有我军炸毁的桥梁, 而且会重新随机资源分布 (但可以保证的是, 资源不会分布到 $1$ 号岛屿上) . 不过侦查部门还发现了这台机器只能够使用 $m$ 次, 所以我们只需要把每次任务完成即可

## 输入
第一行一个整数 $n$, 表示岛屿数量
接下来 $n-1$ 行, 每行三个整数 $u,v,w$ , 表示 $u$ 号岛屿和 $v$ 号岛屿由一条代价为 $w$ 的桥梁直接相连
第 $n+1$ 行, 一个整数 $m$ , 代表敌方机器能使用的次数
接下来 $m$ 行, 第 $i$ 行一个整数 $k_i$ , 代表第 $i$ 次后, 有 $k_i$ 个岛屿资源丰富. 接下来 $k_i$ 个整数 $h_1,h_2,..., h_{k_i}$ , 表示资源丰富岛屿的编号
$2\leq n \leq 2.5\times 10^5, 1\leq m\leq 5\times 10^5, \sum k_i \leq 5\times 10^5, 1\leq k_i< n, h_i\neq 1, 1\leq u,v\leq n, 1\leq w\leq 10^5$

## 输出
输出共 $m$ 行, 表示每次任务的最小代价
*/

/*
10
1 5 13
1 9 6
2 1 19
2 4 8
2 3 91
5 6 8
7 5 4
7 8 31
10 7 9
3
2 10 6
4 5 7 8 3
3 9 4 6
============
12
32
22
*/