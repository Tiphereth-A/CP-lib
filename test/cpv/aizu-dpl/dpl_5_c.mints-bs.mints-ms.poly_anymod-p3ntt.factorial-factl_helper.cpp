#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_C"

#include "../../../src/comb/ball_box/ddl/lib.hpp"
#include "../../../src/comb/binom/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000000 + 7;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/bs/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"
#include "../../../src/math/fact/helper_l/lib.hpp"

using namespace tifa_libs;
using mint = mint_bs<MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = mint_ms<167772161>;
using mint_p3ntt2 = mint_ms<469762049>;
using mint_p3ntt3 = mint_ms<754974721>;
using poly = poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;
using namespace tifa_libs;
using fact_t = factl_helper<poly>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  tifa_libs::binom<mint, fact_t> binom(2001);
  std::cout << tifa_libs::ball_box_ddl<mint>(n, k, binom) << '\n';
  return 0;
}
