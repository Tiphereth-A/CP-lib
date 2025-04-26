#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit"

#include "../../include/comb/gen_pows.hpp"
#include "../../include/math/series_ipaf.hpp"

CEXP u32 MOD = 998244353;

#include "../../include/math/factl_helper.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"
#include "../../include/poly/polymtt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s30, MOD>;
using poly = tifa_libs::math::polymtt<mint>;
using fact_t = tifa_libs::math::factl_helper<poly>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 r, d;
  std::cin >> r >> d;
  auto p = tifa_libs::math::gen_pows<mint>(d + 1, d);
  std::cout << tifa_libs::math::series_ipaf<mint, fact_t>(p, mint(r));
  return 0;
}
