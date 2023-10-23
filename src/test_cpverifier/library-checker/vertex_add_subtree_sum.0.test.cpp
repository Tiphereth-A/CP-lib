#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include "../../code/ds/hld.hpp"
#include "../../code/util/fastio.hpp"

using T = std::pair<i64, i32>;
using F = i64;

T op(T a, T b) { return T{a.first + b.first, a.second + b.second}; }
T e() { return T{0, 0}; }
T mapping(F f, T a) { return T{f + a.first, a.second}; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
  usz n, q;
  tifa_libs::fin >> n >> q;
  vec<i64> b(n);
  vec<T> a(n);
  for (auto& x : b) tifa_libs::fin >> x;
  tifa_libs::graph::tree tr_(n);
  for (usz i = 1, p; i < n; ++i) tifa_libs::fin >> p, tr_.add_arc(p, i);
  tifa_libs::ds::heavy_chain_s<T, op, e, F, mapping, composition, id> tr(tr_);
  for (usz i = 0; i < n; ++i) a[tr_.dfn[i]].first = b[i], a[tr_.dfn[i]].second = 1;
  tr.build(a);
  for (usz i = 0, opt, u; i < q; ++i) {
    tifa_libs::fin >> opt >> u;
    if (opt == 0) {
      i64 x;
      tifa_libs::fin >> x;
      tr.node_update(u, x);
    } else tifa_libs::fout << tr.subtree_query(u).first << '\n';
  }
  return 0;
}
