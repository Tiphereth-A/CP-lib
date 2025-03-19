#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/tree/lca_hld.hpp"
#include "../../include/tree/tree.hpp"

int main() {
  u32 n, q;
  tifa_libs::fin >> n >> q;
  tifa_libs::graph::tree t(n);
  for (u32 i = 1, x; i < n; ++i) tifa_libs::fin >> x, t.add_arc(i, x), t.add_arc(x, i);
  tifa_libs::graph::lca_hld::tree_info_t info(t);
  tifa_libs::graph::lca_hld lca(t, info);
  for (u32 i = 0, u, v; i < q; ++i) {
    tifa_libs::fin >> u >> v;
    tifa_libs::fout << lca(u, v) << '\n';
  }
  return 0;
}
