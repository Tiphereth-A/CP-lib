#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/many_factorials"

#include "../../code/math/factl_helper.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s63, MOD>;
using poly = tifa_libs::math::polyntt<mint>;

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
