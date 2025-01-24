#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include "../../code/ds/segtree.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s30, MOD>;
using T = std::pair<mint, usz>;   // sum len
using F = std::pair<mint, mint>;  // mul add

auto op(T a, T b) { return T{a.first + b.first, a.second + b.second}; }
void mapping(T& a, F f) {
  a.first = f.first * a.first + f.second * a.second;
}
void composition(F& f, F g) {
  f = F{f.first * g.first, g.first * f.second + g.second};
  // g(x) = g.mul * x + g.add
  // f(g(x)) = f.mul * (g.mul * x + g.add) + f.add = f.mul * g.mul * x + f.mul * g.add + f.add
}

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  vec<T> a(n);
  for (auto &x : a) std::cin >> x.first, x.second = 1;
  tifa_libs::ds::segtree<T, op, F, mapping, composition> segt({0, 0}, {1, 0}, a);
  flt_ (u32, i, 1, q + 1) {
    u32 opt, l, r;
    std::cin >> opt >> l;
    if (opt == 0) {
      mint x, y;
      std::cin >> r >> x >> y;
      segt.update(l, r, F{x, y});
    } else
      std::cout << segt.query(l).first << '\n';
  }
  return 0;
}
