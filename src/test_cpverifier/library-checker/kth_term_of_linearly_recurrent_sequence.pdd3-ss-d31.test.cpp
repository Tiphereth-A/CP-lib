#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include "../../code/math/mint_d31.hpp"
#include "../../code/math/mdata_ss.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/nth_term_lrec.hpp"
#include "../../code/poly/polydata_d3ntt.hpp"
#include "../../code/util/ios_container.hpp"

using mdata1 = tifa_libs::math::mdata_ss<167772161>;
using mdata2 = tifa_libs::math::mdata_ss<469762049>;
using mdata3 = tifa_libs::math::mdata_ss<754974721>;
using mint = tifa_libs::math::mint_d31<-1>;
using mint1 = tifa_libs::math::mint<mdata1>;
using mint2 = tifa_libs::math::mint<mdata2>;
using mint3 = tifa_libs::math::mint<mdata3>;
using polyd = tifa_libs::math::polydata_d3ntt<mint, mint1, mint2, mint3>;
using poly = tifa_libs::math::poly<polyd>;

int main() {
  mint::set_mod(998244353);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 d;
  u64 k;
  std::cin >> d >> k;
  vec<mint> a(d), c(d + 1);
  std::cin >> a;
  c[0] = 1;
  for (u32 i = 1; i <= d; ++i) {
    std::cin >> c[i];
    c[i] = -c[i];
  }
  std::cout << tifa_libs::math::nth_term_lrec<polyd>(k, a, c) << '\n';
  return 0;
}
