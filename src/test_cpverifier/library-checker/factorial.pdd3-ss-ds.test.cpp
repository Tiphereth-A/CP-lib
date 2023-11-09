#define PROBLEM "https://yukicoder.me/problems/no/502"

#include "../../code/math/fact_mint.hpp"
#include "../../code/math/mint_ds.hpp"
#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polydata_d3ntt.hpp"

constexpr u64 MOD = 998244353;

using mint = tifa_libs::math::mint_ds<-1>;
using mint1 = tifa_libs::math::mint_ss<167772161>;
using mint2 = tifa_libs::math::mint_ss<469762049>;
using mint3 = tifa_libs::math::mint_ss<754974721>;
using pldt_t = tifa_libs::math::polydata_d3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
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
