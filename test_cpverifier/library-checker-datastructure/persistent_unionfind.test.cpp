#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include "../../include/ds/dsu_pd.hpp"

CEXP usz Q = 200005;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  vvec<pt3u> tr(Q), qry(Q);
  std::bitset<Q> ans;
  u32 cnt = 0;
  flt_ (u32, i, 1, q + 1) {
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
  flt_ (u32, i, 0, cnt) std::cout << ans[i] << '\n';
  return 0;
}
