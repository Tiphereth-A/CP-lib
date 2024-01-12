#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "../../code/math/fact_mint.hpp"
#include "../../code/math/mdata_ds.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/poly/polydata_d3ntt.hpp"

constexpr u64 MOD = 998244353;

using mdata = tifa_libs::math::mdata_ds<-1>;
using mdata1 = tifa_libs::math::mdata_ss<167772161>;
using mdata2 = tifa_libs::math::mdata_ss<469762049>;
using mdata3 = tifa_libs::math::mdata_ss<754974721>;
using mint = tifa_libs::math::mint<mdata>;
using mint1 = tifa_libs::math::mint<mdata1>;
using mint2 = tifa_libs::math::mint<mdata2>;
using mint3 = tifa_libs::math::mint<mdata3>;
using pldt_t = tifa_libs::math::polydata_d3ntt<mint, mint1, mint2, mint3>;

int main() {
  mdata::set_mod(MOD);
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
