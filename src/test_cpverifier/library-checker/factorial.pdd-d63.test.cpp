#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "../../code/math/fact_mint.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_d63.hpp"
#include "../../code/poly/polydata_d.hpp"

constexpr u64 MOD = 998244353;

using mintdata = tifa_libs::math::mintdata_d63<-1>;
using mint = tifa_libs::math::mint<mintdata>;
using pldt_t = tifa_libs::math::polydata_d<mint>;

int main() {
  mintdata::set_mod(MOD);
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
