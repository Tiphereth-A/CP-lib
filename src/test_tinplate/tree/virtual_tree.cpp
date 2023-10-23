#define PROBLEM "https://www.luogu.com.cn/problem/P2495"

#include "../../code/tree/virtual_tree.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<u32> sign(n), min_(n);
  using Tw = u32;
  tifa_libs::graph::tree<Tw> tr(n);
  for (u32 i = 1, u, v, w; i < n; ++i) std::cin >> u >> v >> w, --u, --v, tr.add_edge(u, v, w);
  auto dfs = [&](auto&& dfs, u32 u, u32 fa, u32 min__) -> void {
    min_[u] = min__;
    for (auto v : tr[u])
      if (v.to != fa) dfs(dfs, v.to, u, std::min(min__, v.w));
  };
  dfs(dfs, 0, 0, INT32_MAX);
  tifa_libs::graph::virtual_tree<Tw> vt(tr);
  u32 m, k;
  std::cin >> m;
  for (u32 i = 0; i < m; ++i) {
    std::cin >> k;
    vec<u32> a(k);
    for (auto& x : a) std::cin >> x, --x, sign[x] = 1;
    vt.build(a);
    auto dp = [&](auto&& dp, u32 u) -> u64 {
      if (sign[u]) return min_[u];
      u64 ret = 0;
      for (auto v : vt.vt[u]) ret += dp(dp, v.to);
      return u ? std::min(u64(min_[u]), ret) : ret;
    };
    std::cout << dp(dp, 0) << '\n';
    for (u32 i = 0; i < k; ++i) sign[a[i]] = 0;
  }
  return 0;
}
