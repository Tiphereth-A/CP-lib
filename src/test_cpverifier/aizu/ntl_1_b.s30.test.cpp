#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"

#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s30.hpp"
#include "../../code/math/qpow.hpp"

constexpr u32 MOD = 1'000'000'007;
using mintdata = tifa_libs::math::mintdata_s30<MOD>;
using mint = tifa_libs::math::mint<mintdata>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 m, n;
  std::cin >> m >> n;
  std::cout << tifa_libs::math::qpow(mint(m), n).val() << '\n';
  return 0;
}
