#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../code/io/fastio.hpp"
#include "../../code/tree/lca_hld.hpp"
#include "../../code/tree/tree.hpp"

int main() {
  u32 n, q;
  tifa_libs::fin >> n >> q;
  tifa_libs::graph::tree t(n);
  for (u32 i = 1, x; i < n; ++i) tifa_libs::fin >> x, t.add_arc(i, x), t.add_arc(x, i);
  tifa_libs::graph::lca_hld lca(t);
  for (u32 i = 0, u, v; i < q; ++i) {
    tifa_libs::fin >> u >> v;
    tifa_libs::fout << lca(u, v) << '\n';
  }
  return 0;
}
