#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/io/fastio.hpp"

CEXP u32 MOD = 1000000007;

#include "../../code/conv/conv_3ntt.hpp"
#include "../../code/math/mint_s63.hpp"

using mint = tifa_libs::math::mint_s63<MOD>;
using mint0 = tifa_libs::math::mint_s63<167772161>;
using mint1 = tifa_libs::math::mint_s63<469762049>;
using mint2 = tifa_libs::math::mint_s63<754974721>;
using ntt0_t = tifa_libs::math::NTT<mint0>;
using ntt1_t = tifa_libs::math::NTT<mint1>;
using ntt2_t = tifa_libs::math::NTT<mint2>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  ntt0_t ntt0;
  ntt1_t ntt1;
  ntt2_t ntt2;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt0, ntt1, ntt2, a, b) << '\n';
  return 0;
}
