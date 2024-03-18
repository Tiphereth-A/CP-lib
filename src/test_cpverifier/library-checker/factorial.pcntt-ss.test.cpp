#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "../../code/math/fact_mint.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polycntt.hpp"

constexpr u64 MOD = 998244353;

using mint = tifa_libs::math::mint_ss<MOD>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) {
    u64 n;
    std::cin >> n;
    std::cout << tifa_libs::math::fact_mint<poly>(n) << '\n';
  }
  return 0;
}
