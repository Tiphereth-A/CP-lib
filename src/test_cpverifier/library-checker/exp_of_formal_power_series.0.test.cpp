#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_exp.hpp"
#include "../../code/poly/polydata_s.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_s<mint>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  poly_t p(n);
  std::cin >> p;
  std::cout << tifa_libs::math::poly_exp(p);
  return 0;
}
