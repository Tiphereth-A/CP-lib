#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/io/fastio.hpp"

CEXP u32 MOD = 1000000007;

#include "../../code/conv/conv_3ntt.hpp"
#include "../../code/math/mint_d63.hpp"
#include "../../code/math/mint_s63.hpp"

using mint = tifa_libs::math::mint_d63<-1>;
using mint0 = tifa_libs::math::mint_s63<167772161>;
using mint1 = tifa_libs::math::mint_s63<469762049>;
using mint2 = tifa_libs::math::mint_s63<754974721>;
using ntt3_t = std::tuple<tifa_libs::math::NTT<mint0>, tifa_libs::math::NTT<mint1>, tifa_libs::math::NTT<mint2>>;

int main() {
  mint::set_mod(MOD);
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
  return 0;
}
