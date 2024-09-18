#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite/"

#include "../../code/ds/hld.hpp"
#include "../../code/tree/lca_hld.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using Ty = mint;
using T = std::pair<Ty, Ty>;
using F = T;

constexpr auto op_ab(T a, T b) {  // a(b(x))
  return T{a.first * b.first, a.first * b.second + a.second};
}
constexpr auto op_ba(T a, T b) {  // b(a(x))
  return op_ab(b, a);
}
constexpr auto e() { return T{1, 0}; }
constexpr auto id() { return F{1, 0}; }
constexpr auto mapping(T, F a) { return T{a}; }
constexpr auto composition(F, F) { return F{1, 0}; }

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  vec<T> a(n);
  for (auto &x : a) std::cin >> x.first >> x.second;
  tifa_libs::graph::tree tr(n);
  for (u32 i = 1, u, v; i < n; ++i) std::cin >> u >> v, tr.add_arc(u, v), tr.add_arc(v, u);
  tifa_libs::graph::lca_hld lca(tr);
  tifa_libs::ds::hld<T, op_ba, e, F, mapping, composition, id> hld(tr, a);
  tifa_libs::ds::hld<T, op_ab, e, F, mapping, composition, id> hld1(tr, a);
  for (u32 i = 0, opt; i < q; ++i) {
    std::cin >> opt;
    if (opt == 0) {
      u32 x;
      Ty y, z;
      std::cin >> x >> y >> z;
      hld.node_update(x, F(y, z)), hld1.node_update(x, F(y, z));
    } else {
      u32 x, y;
      Ty z;
      std::cin >> x >> y >> z;
      auto [retu, retv] = lca.getchain(x, y);
      T ret1 = e(), ret2 = e();
      for (auto x : retu) ret1 = op_ba(ret1, hld1.chain_query(x.first, x.second));
      for (auto x : retv) ret2 = op_ba(ret2, hld.chain_query(x.first, x.second));
      ret1 = op_ba(ret1, ret2);
      std::cout << ret1.first * z + ret1.second << '\n';
    }
  }
  return 0;
}