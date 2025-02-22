#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/io/ios_container.hpp"

CEXP u32 MOD = 1000000007;

#include "../../code/conv/conv_mtt.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s30, MOD>;
using vec_t = vec<mint>;
auto conv_func(vec_t CR a, vec_t CR b) {
  tifa_libs::math::FFT_R2<long double> fft;
  return tifa_libs::math::conv_mtt(fft, a, b);
}

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
