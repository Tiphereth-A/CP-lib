#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include "../../include/ds/fenwick.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/tree/dfs_info.hpp"
#include "../../include/tree/dsu_on_tree.hpp"
#include "../../include/tree/tree.hpp"

using namespace tifa_libs;
CEXP i64 INF = std::numeric_limits<i64>::max() / 2;

int main() {
  u32 n, q;
  fin_uint >> n >> q;
  vecii a(n);
  for (auto& x : a) fin_uint >> x;
  graph::tree tr(n);
  for (u32 i = 1, p; i < n; ++i) fin_uint >> p, tr.add_arc((u32)p, (u32)i), tr.add_arc((u32)i, (u32)p);

  vvecpti upd(n);
  vveci que(n);
  flt_ (u32, i, 0, n) upd[i].emplace_back(0, a[i]);
  flt_ (u32, i, 1, q + 1) {
    u32 c, u;
    fin_uint >> c >> u;
    if (c == 0) {
      u32 x;
      fin_uint >> x;
      upd[u].emplace_back(i, x);
    } else que[u].push_back((i32)i);
  }

  ds::fenwick<i64> bit(q + 2);
  vecii ans(q + 1, INF);

  graph::tree_dfs_info<graph::tree, graph::tdi_dfn, graph::tdi_maxson, graph::tdi_maxdfn, graph::tdi_euler> info(tr);
  graph::dsu_on_tree(
      tr, info.dfn, info.sz, info.maxson, info.maxdfn, info.euler,
      [&](u32 i) {
        for (auto&& [j, x] : upd[i]) bit.add(u32(j + 1), x);
      },
      [&](u32 i) {
        for (auto&& j : que[i]) ans[(u32)j] = bit.sum(u32(j + 1));
      },
      [&](u32 i) {
        for (auto&& [j, x] : upd[i]) bit.add(u32(j + 1), -x);
      },
      []() {});
  for (auto&& i : ans)
    if (i != INF) fout << i << '\n';
  return 0;
}
