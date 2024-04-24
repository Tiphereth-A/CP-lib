#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include "../../code/ds/dsu_pd.hpp"

constexpr usz Q = 200005;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  vvec<pt3<u32>> tr(Q), qry(Q);
  std::bitset<Q> ans;
  u32 cnt = 0;
  for (u32 i = 1; i <= q; ++i) {
    u32 t, u, v;
    i32 k;
    std::cin >> t >> k >> u >> v;
    ++k;
    if (t == 0)
      tr[(u32)k].emplace_back(i, u, v);
    else
      qry[(u32)k].emplace_back(cnt++, u, v);
  }
  tifa_libs::ds::dsu_pd dsu(n + 1);
  auto dfs = [&](auto&& dfs, u32 v) -> void {
    for (auto [i, x, y] : qry[v]) ans[i] = dsu.same(x, y);
    for (auto [_, x, y] : tr[v]) {
      auto t = dsu.time();
      dsu.merge(x, y);
      dfs(dfs, _);
      dsu.rollback(t);
    }
  };
  dfs(dfs, 0);
  for (u32 i = 0; i < cnt; ++i) std::cout << ans[i] << '\n';
  return 0;
}
