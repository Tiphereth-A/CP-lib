#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_D"

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
  fin_uint >> n;
  vecii b(n, 0);
  vec<T> a(n);
  graph::tree tr_(n);
  for (u32 u = 0, k; u < n; ++u) {
    fin_uint >> k;
    for (u32 i = 0, v; i < k; ++i) fin_uint >> v, tr_.add_edge(u, v);
  }
  graph::hld<T, op, F, mapping, composition> tr({0, 0}, 0, tr_);
  flt_ (u32, i, 0, n) a[tr.info.dfn[i]].first = b[i], a[tr.info.dfn[i]].second = 1;
  tr.build(a);
  fin_uint >> q;
  for (u32 i = 0, opt, u; i < q; ++i) {
    fin_uint >> opt >> u;
    if (opt == 0) {
      i64 x;
      fin_uint >> x;
      tr.node_update((u32)u, x);
    } else {
      fout << tr.chain_query((u32)u, 0).first << '\n';
    }
  }
  return 0;
}
