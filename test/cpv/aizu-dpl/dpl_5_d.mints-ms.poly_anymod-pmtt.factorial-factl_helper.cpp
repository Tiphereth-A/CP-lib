#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_D"

#include "../../../src/comb/ball_box/ida/lib.hpp"
#include "../../../src/comb/binom/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000000 + 7;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"
#include "../../../src/math/fact/helper_l/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms<MOD>;
using namespace tifa_libs;
using poly = polymtt<mint>;
using namespace tifa_libs;
using fact_t = factl_helper<poly>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::binom<mint, fact_t> binom(2001);
  std::cout << tifa_libs::ball_box_ida<mint>(n, k, binom) << '\n';
  return 0;
}
