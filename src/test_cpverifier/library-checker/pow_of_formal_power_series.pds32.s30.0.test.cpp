#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_pow.hpp"
#include "../../code/poly/polydata_s32.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_s32<mint>>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  tifa_libs::u64 m;
  std::cin >> n >> m;
  poly_t a(n);
  std::cin >> a;
  std::cout << tifa_libs::math::poly_pow(a, m) << '\n';
  return 0;
}
