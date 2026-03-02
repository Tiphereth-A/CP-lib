#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit"

#include "../../../src/comb/seq/pows/lib.hpp"
#include "../../../src/math/ipaf/series/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/fact/helper_l/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"
#include "../../../src/math/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms64, MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_bs, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_bs, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_bs, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;
using namespace tifa_libs;
using fact_t = math::factl_helper<poly>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 r, d;
  std::cin >> r >> d;
  auto p = tifa_libs::math::gen_pows<mint>(d + 1, d);
  std::cout << tifa_libs::math::series_ipaf<mint, fact_t>(p, mint(r));
  return 0;
}
