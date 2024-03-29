#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"

#include "../../code/comb/gen_stirling1_row.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_ss<MOD>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  std::cout << tifa_libs::math::gen_stirling1_row<poly>(n);
  return 0;
}
