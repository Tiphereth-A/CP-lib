#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/io/fastio.hpp"

CEXP u32 MOD = 1000000007;

#include "../../code/conv/conv_mtt.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;

int main() {
  mint::set_mod(MOD);
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec<mint> a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::math::FFT<long double> fft;
  tifa_libs::fout << tifa_libs::math::conv_mtt(fft, a, b) << '\n';
  return 0;
}
