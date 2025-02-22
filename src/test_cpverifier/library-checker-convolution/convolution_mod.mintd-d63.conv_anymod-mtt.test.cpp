#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/io/ios_container.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/conv/conv_mtt.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d63.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d63, __LINE__>;
using vec_t = vec<mint>;
auto conv_func(vec_t CR a, vec_t CR b) {
  tifa_libs::math::FFT_R2<long double> fft;
  return tifa_libs::math::conv_mtt(fft, a, b);
}

int main() {
  mint::set_mod(MOD);
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
