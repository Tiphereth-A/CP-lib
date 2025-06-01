#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/tree/hld.hpp"

using namespace tifa_libs;
using T = std::pair<i64, i32>;
using F = i64;

T op(T a, T b) { return T{a.first + b.first, a.second + b.second}; }
void mapping(T& a, F f) { a.first += f; }
void composition(F& f, F g) { f += g; }

int main() {
  u32 n, q;
  fin >> n >> q;
  vecii b(n);
  vec<T> a(n);
  for (auto& x : b) fin >> x;
  graph::tree tr_(n);
  for (u32 i = 1, p; i < n; ++i) fin >> p, tr_.add_arc((u32)p, (u32)i);
  graph::hld<T, op, F, mapping, composition> tr({0, 0}, 0, tr_);
  flt_ (u32, i, 0, n) a[tr.info.dfn[i]].first = b[i], a[tr.info.dfn[i]].second = 1;
  tr.build(a);
  for (u32 i = 0, opt, u; i < q; ++i) {
    fin >> opt >> u;
    if (opt == 0) {
      i64 x;
      fin >> x;
      tr.node_update((u32)u, x);
    } else fout << tr.subtree_query((u32)u).first << '\n';
  }
  return 0;
}
