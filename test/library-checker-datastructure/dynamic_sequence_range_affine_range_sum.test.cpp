#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include "../../include/ds/fhq_treap_w.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, 998244353>;
using T = std::pair<mint, usz>;   // sum len
using F = std::pair<mint, mint>;  // mul add

auto op(T a, T b) { return T{a.first + b.first, a.second + b.second}; }
auto e() { return T{0, 0}; }
auto mapping(F f, T a) {
  return T{f.first * a.first + f.second * a.second, a.second};
}
auto composition(F f, F g) {
  return F{f.first * g.first, f.first * g.second + f.second};
  // g(x) = g.mul * x + g.add
  // f(g(x)) = f.mul * (g.mul * x + g.add) + f.add = f.mul * g.mul * x + f.mul * g.add + f.add
}
auto id() { return F(1, 0); }

int main() {
  u32 n, q;
  mint x, y;
  fin >> n >> q;
  ds::fhq_treap_w<T, op, e, F, mapping, composition, id, true> tr(n + q);
  flt_ (u32, i, 0, n)
    fin >> x, tr.insert(T{x, 1});
  for (u32 i = 0, opt, l, r; i < q; ++i) {
    fin >> opt >> l;
    if (opt == 0) fin >> x, tr.insert(T{x, 1}, l);
    else if (opt == 1) tr.erase(l);
    else if (opt == 2) fin >> r, tr.reverse(l, r - 1);
    else if (opt == 3) fin >> r >> x >> y, tr.update(l, r - 1, T(x, y));
    else fin >> r, fout << tr.query(l, r - 1).first << '\n';
  }
  return 0;
}
