#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"

#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/poly/poly_czt.hpp"
#include "../../code/poly/polydata_scntt.hpp"

using mdata = tifa_libs::math::mint_ss<998244353>;
using mint = tifa_libs::math::mint<mdata>;
using polyd = tifa_libs::math::polydata_scntt<mint>;
using poly = tifa_libs::math::poly<polyd>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  mint a, r;
  std::cin >> n >> m >> a >> r;
  poly f(n);
  std::cin >> f;
  std::cout << tifa_libs::math::poly_czt(f, r, m, a) << '\n';
  return 0;
}
