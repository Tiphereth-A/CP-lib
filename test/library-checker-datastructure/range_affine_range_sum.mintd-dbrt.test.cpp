#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../../include/ds/segtree.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_dbrt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_dbrt, __LINE__>;
using T = std::pair<mint, usz>;   // sum len
using F = std::pair<mint, mint>;  // mul add

auto op(T a, T b) { return T{a.first + b.first, a.second + b.second}; }
auto mapping(T& a, F f) { a.first = f.first * a.first + f.second * a.second; }
auto composition(F& f, F g) {
  f = F{f.first * g.first, g.first * f.second + g.second};
  // g(x) = g.mul * x + g.add
  // f(g(x)) = f.mul * (g.mul * x + g.add) + f.add = f.mul * g.mul * x + f.mul * g.add + f.add
}

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  vec<T> a(n);
  for (auto& x : a) std::cin >> x.first, x.second = 1;
  tifa_libs::ds::segtree<T, op, F, mapping, composition> segt({0, 0}, {1, 0}, a);
  flt_ (u32, i, 1, q + 1) {
    u32 opt, l, r;
    std::cin >> opt >> l >> r;
    if (opt == 0) {
      mint x, y;
      std::cin >> x >> y;
      segt.update(l, r, F{x, y});
    } else
      std::cout << segt.query(l, r).first << '\n';
  }
  return 0;
}
