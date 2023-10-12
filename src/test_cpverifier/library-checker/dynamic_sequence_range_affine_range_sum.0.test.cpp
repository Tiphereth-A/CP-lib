#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include "../../code/ds/fhq_treap.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using T = std::pair<mint, size_t>;  // sum len
using F = std::pair<mint, mint>;    // mul add

auto op(T a, T b) { return T{a.first + b.first, a.second + b.second}; }
auto e() { return T{0, 0}; }
auto mapping(F f, T a) {
  return T{f.first * a.first + f.second * a.second, a.second};
}
auto composition(F f, F g) {
  return F{f.first * g.first, f.first * g.second + f.second};
  /*
  g(x) = g.mul * x + g.add
  f(g(x)) = f.mul * (g.mul * x + g.add) + f.add = f.mul * g.mul * x + f.mul * g.add + f.add
  */
}
auto id() { return F(1, 0); }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n, q;
  mint x, y;
  std::cin >> n >> q;
  tifa_libs::ds::fhq_treap_w<mint, T, op, e, F, mapping, composition, id, true> tr(n + q);
  for (size_t i = 0; i < n; ++i)
    std::cin >> x, tr.insert(T{x, 1});
  for (size_t i = 0, opt, l, r; i < q; ++i) {
    std::cin >> opt >> l;
    if (opt == 0) std::cin >> x, tr.insert(T{x, 1}, l);
    else if(opt == 1) tr.erase(l);
    else if(opt == 2) std::cin >> r, tr.reverse(l, r - 1);
    else if(opt == 3) std::cin >> r >> x >> y, tr.update(l, r - 1, T(x, y));
    else std::cin >> r, std::cout << tr.query(l, r - 1).first << '\n';
  }
  return 0;
}
