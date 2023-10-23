#define PROBLEM "https://yukicoder.me/problems/no/502"

#include "../../code/math/fact_mint.hpp"
#include "../../code/math/mint_d31.hpp"
#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polydata_d3ntt.hpp"

constexpr u64 MOD = 1000000007;

using mint = tifa_libs::math::mint_d31<-1>;
using mint1 = tifa_libs::math::mint_s30<167772161>;
using mint2 = tifa_libs::math::mint_s30<469762049>;
using mint3 = tifa_libs::math::mint_s30<754974721>;
using pldt_t = tifa_libs::math::polydata_d3ntt<mint, mint1, mint2, mint3>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::fact_mint<pldt_t>(n) << '\n';
  return 0;
}
