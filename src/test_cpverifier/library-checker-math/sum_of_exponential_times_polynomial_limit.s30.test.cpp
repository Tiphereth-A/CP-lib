#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit"

#include "../../code/comb/gen_pows.hpp"
#include "../../code/math/series_ipaf.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 r, d;
  std::cin >> r >> d;
  auto p = tifa_libs::math::gen_pows<mint>(d + 1, d);
  std::cout << tifa_libs::math::series_ipaf(p, mint(r));
  return 0;
}
