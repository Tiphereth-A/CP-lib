#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/many_factorials"

#include "../../code/math/factl_helper.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/poly3ntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using mint1 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 167772161>;
using mint2 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 469762049>;
using mint3 = tifa_libs::math::mint<tifa_libs::math::mint_s63, 754974721>;
using poly = tifa_libs::math::poly3ntt<mint, mint1, mint2, mint3>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    u32 n;
    std::cin >> n;
    std::cout << tifa_libs::math::factl_helper<poly>::get_fact(n) << '\n';
  }
  return 0;
}
