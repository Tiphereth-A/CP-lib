#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"

#include "../../code/math/mint_s30.hpp"
#include "../../code/math/qpow.hpp"

constexpr tifa_libs::u32 MOD = 1'000'000'007;
using mint = tifa_libs::math::mint_s30<MOD>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 m, n;
  std::cin >> m >> n;
  std::cout << tifa_libs::math::qpow(mint(m), n).val() << '\n';
  return 0;
}
