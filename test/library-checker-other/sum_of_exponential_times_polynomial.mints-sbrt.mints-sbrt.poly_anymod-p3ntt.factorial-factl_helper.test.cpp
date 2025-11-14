#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial"

#include "../../include/comb/gen_pows.hpp"
#include "../../include/math/sum_ipaf.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/factl_helper.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_sbrt.hpp"
#include "../../include/poly/poly3ntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_sbrt, MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_sbrt, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_sbrt, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_sbrt, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;
using namespace tifa_libs;
using fact_t = math::factl_helper<poly>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 r, d;
  u64 n;
  std::cin >> r >> d >> n;
  auto p = tifa_libs::math::gen_pows<mint>(d + 1, d);
  std::cout << tifa_libs::math::sum_ipaf<mint, fact_t>(p, mint(r), n);
  return 0;
}
