#define PROBLEM "https://yukicoder.me/problems/no/963"

#include "../../code/math/fact_mint.hpp"
#include "../../code/math/mint_d31.hpp"
#include "../../code/poly/polydata_d.hpp"

constexpr tifa_libs::u64 MOD = 1000000007;

using mint = tifa_libs::math::mint_d31<-1>;
using pldt_t = tifa_libs::math::polydata_d<mint>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n;
  std::cin >> n;
  if (n >= MOD) {
    std::cout << "0\n";
    return 0;
  }
  std::cout << tifa_libs::math::fact_mint<pldt_t>(n);
  return 0;
}
