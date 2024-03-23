#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "../../code/poly/poly_inv.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint_s63<MOD>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  poly p(n);
  std::cin >> p;
  std::cout << tifa_libs::math::poly_inv(p);
  return 0;
}
