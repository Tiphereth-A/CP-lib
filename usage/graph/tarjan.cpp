#define PROBLEM "https://www.luogu.com.cn/problem/P3387"

#include "../../include/graph/tarjan.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  vecu a(n);
  for (auto& x : a) std::cin >> x;
  vvecu e(n);
  for (u32 i = 0, u, v; i < m; ++i) std::cin >> u >> v, e[u - 1].push_back(v - 1);
  graph::tarjan scc;
  scc.build(e);
  vvecu g(scc.id);
  vecu in(scc.id), b(scc.id), dp(scc.id, 1'000'000'000);
  for (u32 i = 0, x, y; i < n; ++i) {
    for (b[x = scc.scc_id[i]] += a[i]; auto v : e[i])
      if (x != (y = scc.scc_id[v])) g[x].push_back(y), ++in[y];
  }
  auto dfs = [&](auto&& dfs, u32 u) -> void {
    if (dp[u] != 1'000'000'000) return;
    for (dp[u] = b[u]; auto v : g[u]) dfs(dfs, v), dp[u] = std::max(dp[u], b[u] + dp[v]);
  };
  u32 ret = 0;
  flt_ (u32, i, 0, scc.id)
    if (!in[i]) dfs(dfs, i), ret = std::max(ret, dp[i]);
  std::cout << ret;
}

/*
给定一个 $n$ 个点 $m$ 条边有向图, 每个点有一个权值, 求一条路径, 使路径经过的点权值之和最大. 你只需要求出这个权值和
允许多次经过一条边或者一个点, 但是, 重复经过的点, 权值只计算一次

## 输入
第一行两个正整数 $n,m$
第二行 $n$ 个整数, 其中第 $i$ 个数 $a_i$ 表示点 $i$ 的点权
第三至 $m+2$ 行, 每行两个整数 $u,v$, 表示一条 $u\rightarrow v$ 的有向边
$1\le n \le 10^4$, $1\le m \le 10^5$, $0\le a_i\le 10^3$

## 输出
共一行, 最大的点权之和
*/

/*
2 2
1 1
1 2
2 1
======
2
*/