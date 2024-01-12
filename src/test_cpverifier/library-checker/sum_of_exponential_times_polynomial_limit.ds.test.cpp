#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit"

#include "../../code/comb/gen_pows.hpp"
#include "../../code/math/mdata_ds.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/series_ipaf.hpp"

constexpr u32 MOD = 998244353;
using mdata = tifa_libs::math::mdata_ds<-1>;
using mint = tifa_libs::math::mint<mdata>;

int main() {
  mdata::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 r, d;
  std::cin >> r >> d;
  auto p = tifa_libs::math::gen_pows<mint>(d + 1, d);
  std::cout << tifa_libs::math::series_ipaf(p, mint(r));
  return 0;
}
