#define PROBLEM "https://www.luogu.com.cn/problem/P3387"

#include "../../code/graph/tarjan.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<u32> a(n);
  for (auto& x : a) std::cin >> x;
  tifa_libs::graph::adjlist e(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    --u, --v;
    e.add_arc(u, v);
  }
  tifa_libs::graph::tarjan scc(e);
  tifa_libs::graph::adjlist g(scc.id);
  vec<u32> in(scc.id), b(scc.id), dp(scc.id, 1'000'000'000);
  std::queue<u32> q;
  for (u32 i = 0, x, y; i < n; ++i) {
    b[x = scc.scc_id[i]] += a[i];
    for (auto v : e[i])
      if (x != (y = scc.scc_id[v.to])) g.add_arc(x, y), ++in[y];
  }
  auto dfs = [&](auto&& dfs, u32 u) -> void {
    if (dp[u] != 1'000'000'000) return;
    dp[u] = b[u];
    for (auto v : g[u]) {
      dfs(dfs, v.to);
      dp[u] = std::max(dp[u], b[u] + dp[v.to]);
    }
  };
  u32 ret = 0;
  for (u32 i = 0; i < scc.id; ++i)
    if (!in[i]) dfs(dfs, i), ret = std::max(ret, dp[i]);
  std::cout << ret;
  return 0;
}
/*
# 【模板】缩点

## 题目描述

给定一个 $n$ 个点 $m$ 条边有向图，每个点有一个权值，求一条路径，使路径经过的点权值之和最大。你只需要求出这个权值和。

允许多次经过一条边或者一个点，但是，重复经过的点，权值只计算一次。

## 输入格式

第一行两个正整数 $n,m$

第二行 $n$ 个整数，其中第 $i$ 个数 $a_i$ 表示点 $i$ 的点权。

第三至 $m+2$ 行，每行两个整数 $u,v$，表示一条 $u\rightarrow v$ 的有向边。

## 输出格式

共一行，最大的点权之和。

## 样例 #1

### 样例输入 #1

```
2 2
1 1
1 2
2 1
```

### 样例输出 #1

```
2
```

## 提示

对于 $100\%$ 的数据，$1\le n \le 10^4$，$1\le m \le 10^5$，$0\le a_i\le 10^3$。
*/