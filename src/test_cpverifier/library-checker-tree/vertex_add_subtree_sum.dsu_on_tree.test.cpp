#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include "../../code/ds/fenwick.hpp"
#include "../../code/io/fastio.hpp"
#include "../../code/tree/dfs_info.hpp"
#include "../../code/tree/dsu_on_tree.hpp"
#include "../../code/tree/tree.hpp"

CEXP i64 INF = std::numeric_limits<i64>::max() / 2;

int main() {
  u32 n, q;
  tifa_libs::fin >> n >> q;
  vecii a(n);
  for (auto& x : a) tifa_libs::fin >> x;
  tifa_libs::graph::tree tr(n);
  for (u32 i = 1, p; i < n; ++i) tifa_libs::fin >> p, tr.add_arc((u32)p, (u32)i), tr.add_arc((u32)i, (u32)p);

  vvecpti upd(n);
  vveci que(n);
  flt_ (u32, i, 0, n) upd[i].emplace_back(0, a[i]);
  flt_ (u32, i, 1, q + 1) {
    u32 c, u;
    tifa_libs::fin >> c >> u;
    if (c == 0) {
      u32 x;
      tifa_libs::fin >> x;
      upd[u].emplace_back(i, x);
    } else que[u].push_back(i);
  }

  tifa_libs::ds::fenwick<i64> bit(q + 2);
  vecii ans(q + 1, INF);

  tifa_libs::graph::tree_dfs_info<tifa_libs::graph::tree, tifa_libs::graph::tdi_dfn, tifa_libs::graph::tdi_maxson, tifa_libs::graph::tdi_maxdfn, tifa_libs::graph::tdi_euler> info(tr);
  tifa_libs::graph::dsu_on_tree(
      tr, info.dfn, info.sz, info.maxson, info.maxdfn, info.euler,
      [&](u32 i) {
        for (auto&& [j, x] : upd[i]) bit.add(j + 1, x);
      },
      [&](u32 i) {
        for (auto&& j : que[i]) ans[j] = bit.sum(j + 1);
      },
      [&](u32 i) {
        for (auto&& [j, x] : upd[i]) bit.add(j + 1, -x);
      },
      []() {});
  for (auto&& i : ans)
    if (i != INF) tifa_libs::fout << i << '\n';
  return 0;
}
