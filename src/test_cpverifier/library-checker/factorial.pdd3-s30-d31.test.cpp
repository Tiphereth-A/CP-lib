#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "../../code/math/fact_mint.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_d31.hpp"
#include "../../code/math/mintdata_s30.hpp"
#include "../../code/poly/polydata_d3ntt.hpp"

constexpr u64 MOD = 998244353;

using mintdata = tifa_libs::math::mintdata_d31<-1>;
using mintdata1 = tifa_libs::math::mintdata_s30<167772161>;
using mintdata2 = tifa_libs::math::mintdata_s30<469762049>;
using mintdata3 = tifa_libs::math::mintdata_s30<754974721>;
using mint = tifa_libs::math::mint<mintdata>;
using mint1 = tifa_libs::math::mint<mintdata1>;
using mint2 = tifa_libs::math::mint<mintdata2>;
using mint3 = tifa_libs::math::mint<mintdata3>;
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
