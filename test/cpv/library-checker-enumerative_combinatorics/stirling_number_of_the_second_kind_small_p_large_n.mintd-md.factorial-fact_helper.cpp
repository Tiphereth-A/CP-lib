#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_small_p_large_n"

#include "../../../src/comb/stirling2_smallp/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/md/lib.hpp"
#include "../../../src/math/fact/helper/lib.hpp"

using namespace tifa_libs;
using mint = mint_md<__LINE__>;
using namespace tifa_libs;
using fact_t = fact_helper<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t, mod;
  std::cin >> t >> mod;
  mint::set_mod(mod);
  tifa_libs::stirling2<mint, fact_t> S;
  while (t--) {
    u64 n, k;
    std::cin >> n >> k;
    std::cout << S(n, k) << '\n';
  }
  return 0;
}
