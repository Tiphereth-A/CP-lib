#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial"

#include "../../../src/comb/seq/pows/lib.hpp"
#include "../../../src/math/ipaf/sum/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/fact/helper/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bs, MOD>;
using namespace tifa_libs;
using fact_t = math::fact_helper<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 r, d;
  u64 n;
  std::cin >> r >> d >> n;
  auto p = tifa_libs::math::gen_pows<mint>(d + 1, d);
  std::cout << tifa_libs::math::sum_ipaf<mint, fact_t>(p, mint(r), n);
  return 0;
}
