#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/many_factorials"

#include "../../include/util/alias_num.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/factl_helper.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_sbrt.hpp"
#include "../../include/poly/polyntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_sbrt, MOD>;
using namespace tifa_libs;
using poly = math::polyntt<mint>;
using namespace tifa_libs;
using fact_t = math::factl_helper<poly>;

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
