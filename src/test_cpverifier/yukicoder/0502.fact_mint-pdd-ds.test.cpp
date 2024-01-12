#define PROBLEM "https://yukicoder.me/problems/no/502"

#include "../../code/math/fact_mint.hpp"
#include "../../code/math/mdata_ds.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/poly/polydata_d.hpp"

constexpr u64 MOD = 1000000007;

using mdata = tifa_libs::math::mint_ds<-1>;
using mint = tifa_libs::math::mint<mdata>;

using pldt_t = tifa_libs::math::polydata_d<mint>;

int main() {
  mdata::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::fact_mint<pldt_t>(n) << '\n';
  return 0;
}
