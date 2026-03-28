#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit"

#include "../../../src/comb/seq/pows/lib.hpp"
#include "../../../src/math/ipaf/series/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"
#include "../../../src/math/fact/helper_l/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms<MOD>;
using namespace tifa_libs;
using poly = polyntt<mint>;
using namespace tifa_libs;
using fact_t = factl_helper<poly>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 r, d;
  std::cin >> r >> d;
  auto p = tifa_libs::gen_pows<mint>(d + 1, d);
  std::cout << tifa_libs::series_ipaf<mint, fact_t>(p, mint(r));
  return 0;
}
