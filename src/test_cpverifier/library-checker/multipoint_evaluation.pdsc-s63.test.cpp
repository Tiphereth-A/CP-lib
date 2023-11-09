#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_mpe.hpp"
#include "../../code/poly/polydata_scntt.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_scntt<mint>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  poly_t a(n), p(m);
  std::cin >> a >> p;
  std::cout << tifa_libs::math::poly_mpe(a, p) << '\n';
  return 0;
}
