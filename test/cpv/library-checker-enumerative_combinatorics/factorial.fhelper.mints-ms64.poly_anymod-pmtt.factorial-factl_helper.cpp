#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "../../../src/util/alias/num/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/ms64/lib.hpp"
#include "../../../src/math/fact/helper_l/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms64<MOD>;
using namespace tifa_libs;
using poly = polymtt<mint>;
using namespace tifa_libs;
using fact_t = factl_helper<poly>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    u32 n;
    std::cin >> n;
    std::cout << fact_t::get_fact(n) << '\n';
  }
  return 0;
}
