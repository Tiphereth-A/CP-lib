#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial"

#include "../../code/comb/gen_pows.hpp"
#include "../../code/math/mint_ds.hpp"
#include "../../code/math/sum_ipaf.hpp"

constexpr u32 MOD = 998244353;
using mint = tifa_libs::math::mint_ds<-1>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 r, d, n;
  std::cin >> r >> d >> n;
  auto p = tifa_libs::math::gen_pows<mint>(d + 1, d);
  std::cout << tifa_libs::math::sum_ipaf(p, mint(r), n);
  return 0;
}
