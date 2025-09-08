#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000007;

#include "../../include/conv/conv_mtt.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, MOD>;
using namespace tifa_libs;
using vec_t = vec<mint>;
auto conv_func(vec_t CR a, vec_t CR b) {
  math::fft_r2<long double> fft;
  return math::conv_mtt(fft, a, b);
}

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
