#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"

#include "../../code/comb/gen_stirling2_row.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polydata_s32.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using polyd = tifa_libs::math::polydata_s32<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  std::cout << tifa_libs::math::gen_stirling2_row<polyd>(n);
  return 0;
}
