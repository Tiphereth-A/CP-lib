#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_E"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/tree/hld.hpp"

using T = std::pair<i64, i32>;
using F = i64;

T op(T a, T b) { return T{a.first + b.first, a.second + b.second}; }
void mapping(T& a, F f) { a.first += f * a.second; }
void composition(F& f, F g) { f += g; }

int main() {
  u32 n, q;
  tifa_libs::fin >> n;
  vecii b(n, 0);
  vec<T> a(n);
  tifa_libs::graph::tree tr_(n);
  for (u32 u = 0, k; u < n; ++u) {
    tifa_libs::fin >> k;
    for (u32 i = 0, v; i < k; ++i) tifa_libs::fin >> v, tr_.add_edge(u, v);
  }
  tifa_libs::graph::hld<T, op, F, mapping, composition> tr({0, 0}, 0, tr_);
  flt_ (u32, i, 0, n) a[tr.info.dfn[i]].first = b[i], a[tr.info.dfn[i]].second = 1;
  tr.build(a);
  tifa_libs::fin >> q;
  for (u32 i = 0, opt, u; i < q; ++i) {
    tifa_libs::fin >> opt >> u;
    if (opt == 0) {
      i64 x;
      tifa_libs::fin >> x;
      tr.chain_update((u32)u, 0, x);
      tr.node_update(0, -x);
    } else {
      tifa_libs::fout << tr.chain_query((u32)u, 0).first << '\n';
    }
  }
  return 0;
}
