#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"

#include "../../code/math/mint_d31.hpp"
#include "../../code/math/qpow.hpp"

constexpr tifa_libs::u64 MOD = 1'000'000'007;
using mint = tifa_libs::math::mint_d31<-1>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  mint m;
  tifa_libs::u64 n;
  std::cin >> m >> n;
  std::cout << tifa_libs::math::qpow(m, n).val() << '\n';
  return 0;
}
