#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "../../code/math/fact_mint.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polydata_s32.hpp"

constexpr u64 MOD = 998244353;

using mint = tifa_libs::math::mint_s30<MOD>;
using pldt_t = tifa_libs::math::polydata_s32<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) {
    u64 n;
    std::cin >> n;
    std::cout << tifa_libs::math::fact_mint<pldt_t>(n) << '\n';
  }
  return 0;
}
