#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_small_p_large_n"

#include "../../include/comb/stirling1_smallp.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/factl_helper.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_dbrt.hpp"
#include "../../include/poly/polymtt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_dbrt, __LINE__>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;
using namespace tifa_libs;
using fact_t = math::factl_helper<poly>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t, mod;
  std::cin >> t >> mod;
  mint::set_mod(mod);
  tifa_libs::math::stirling1<mint, fact_t> s;
  while (t--) {
    u64 n, k;
    std::cin >> n >> k;
    std::cout << s(n, k) << '\n';
  }
  return 0;
}
