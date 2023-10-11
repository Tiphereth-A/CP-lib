#include <cstddef>
#include <iostream>
#include <utility>
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include "../../code/ds/heavy_chain_subdivision.hpp"

using T = std::pair<tifa_libs::i64, tifa_libs::i32>;
using F = tifa_libs::i64;

T op(T a, T b) { return T{a.first + b.first, a.second + b.second}; }
T e() { return T{0, 0}; }
T mapping(F f, T a) { return T{f + a.first, a.second}; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n, q;
  std::cin >> n >> q;
  tifa_libs::vec<tifa_libs::i64> b(n);
  tifa_libs::vec<T> a(n);
  for (auto& x : b) std::cin >> x;
  tifa_libs::ds::heavy_chain_s<T, op, e, F, mapping, composition, id> tr(n);
  for (size_t i = 1, p; i < n; ++i) std::cin >> p, tr.add(p, i);
  tr.subt_req();
  for (size_t i = 0; i < n; ++i) a[tr.dfn[i]].first = b[i], a[tr.dfn[i]].second = 1;
  tr.build(a);
  for (size_t i = 0, opt, u; i < q; ++i) {
    std::cin >> opt >> u;
    if (opt == 0) {
      tifa_libs::i64 x;
      std::cin >> x;
      tr.node_update(u, x);
    } else {
      size_t v;
      std::cin >> v;
      std::cout << tr.chain_query(u, v).first << '\n';
    }
  }
  return 0;
}
