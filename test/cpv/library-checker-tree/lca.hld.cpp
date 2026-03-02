#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/tree/ds/lib.hpp"
#include "../../../src/tree/lca_hld/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 n, q;
  fin_uint >> n >> q;
  graph::tree t(n);
  for (u32 i = 1, x; i < n; ++i) fin_uint >> x, t.add_arc(i, x), t.add_arc(x, i);
  graph::lca_hld::tree_info_t info(t);
  graph::lca_hld lca(t, info);
  for (u32 i = 0, u, v; i < q; ++i) {
    fin_uint >> u >> v;
    fout << lca(u, v) << '\n';
  }
  return 0;
}
