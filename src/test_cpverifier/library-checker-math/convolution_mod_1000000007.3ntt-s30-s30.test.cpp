#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/io/fastio.hpp"

CEXP u32 MOD = 1000000007;

#include "../../code/conv/conv_3ntt.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using mint0 = tifa_libs::math::mint_s30<167772161>;
using mint1 = tifa_libs::math::mint_s30<469762049>;
using mint2 = tifa_libs::math::mint_s30<754974721>;
using ntt3_t = std::tuple<tifa_libs::math::NTT<mint0>, tifa_libs::math::NTT<mint1>, tifa_libs::math::NTT<mint2>>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
  return 0;
}
