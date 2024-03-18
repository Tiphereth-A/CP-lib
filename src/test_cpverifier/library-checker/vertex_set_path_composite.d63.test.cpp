#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite/"

#include "../../code/ds/hld.hpp"
#include "../../code/math/mint_d63.hpp"
#include "../../code/tree/lca_hld.hpp"

using mint = tifa_libs::math::mint_d63<-1>;
using Ty = mint;
using T = std::pair<Ty, Ty>;
using F = T;

auto op(T a, T b) {  // b(a(x))
  swap(a, b);
  return T{a.first * b.first, a.first * b.second + a.second};
}
auto op1(T a, T b) {  // a(b(x))
  return T{a.first * b.first, a.first * b.second + a.second};
}
auto e() { return T{1, 0}; }
auto id() { return e(); }
auto mapping(F f, T a) { return op(f, a); }
auto composition(F, F) { return F(1, 0); }

int main() {
  mint::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  vec<T> a(n);
  for (auto &x : a) std::cin >> x.first >> x.second;
  tifa_libs::graph::tree tr(n);
  for (u32 i = 1, u, v; i < n; ++i) std::cin >> u >> v, tr.add_arc(u, v), tr.add_arc(v, u);
  tifa_libs::graph::lca_hld lca(tr);
  tifa_libs::ds::hld<T, op, e, F, mapping, composition, id> hld(tr, a);
  tifa_libs::ds::hld<T, op1, e, F, mapping, composition, id> hld1(tr, a);
  for (u32 i = 0, opt; i < q; ++i) {
    std::cin >> opt;
    if (opt == 0) {
      u32 x;
      Ty y, z;
      std::cin >> x >> y >> z;
      hld.node_set(x, T(y, z)), hld1.node_set(x, T(y, z));
    } else {
      u32 x, y;
      Ty z;
      std::cin >> x >> y >> z;
      auto [retu, retv] = lca.getchain(x, y);
      T ret1 = e(), ret2 = e();
      for (auto x : retu) ret1 = op(ret1, hld1.chain_query(x.first, x.second));
      for (auto x : retv) ret2 = op(ret2, hld.chain_query(x.first, x.second));
      ret1 = op(ret1, ret2);
      std::cout << ret1.first * z + ret1.second << '\n';
    }
  }
  return 0;
}