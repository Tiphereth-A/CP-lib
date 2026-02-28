#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "../../../src/util/alias/num/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/fact/helper/lib.hpp"
#include "../../../src/math/mint/bd/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bd, __LINE__>;
using namespace tifa_libs;
using fact_t = math::fact_helper<mint>;

int main() {
  mint::set_mod(MOD);
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
