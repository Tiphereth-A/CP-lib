#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/tree/lca_hld.hpp"
#include "../../include/tree/tree.hpp"

using namespace tifa_libs;
int main() {
  u32 n, q;
  fin >> n >> q;
  graph::tree t(n);
  for (u32 i = 1, x; i < n; ++i) fin >> x, t.add_arc(i, x), t.add_arc(x, i);
  graph::lca_hld::tree_info_t info(t);
  graph::lca_hld lca(t, info);
  for (u32 i = 0, u, v; i < q; ++i) {
    fin >> u >> v;
    fout << lca(u, v) << '\n';
  }
  return 0;
}
