#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_small_p_large_n"

#include "../../code/comb/stirling2_smallp.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/factl_helper.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d31.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;
using poly = tifa_libs::math::polymtt<mint>;
using fact_t = tifa_libs::math::factl_helper<poly>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t, mod;
  std::cin >> t >> mod;
  mint::set_mod(mod);
  tifa_libs::math::Stirling2<mint, fact_t> S;
  while (t--) {
    u64 n, k;
    std::cin >> n >> k;
    std::cout << S(n, k) << '\n';
  }
  return 0;
}
