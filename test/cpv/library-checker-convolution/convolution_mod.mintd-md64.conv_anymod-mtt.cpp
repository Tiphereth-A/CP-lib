#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/conv/add/mtt/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/md64/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md64, __LINE__>;
using namespace tifa_libs;
using vec_t = vec<mint>;
auto conv_func(vec_t CR a, vec_t CR b) {
  math::fft_r2<long double> fft;
  return math::conv_mtt(fft, a, b);
}

int main() {
  mint::set_mod(MOD);
  u32 n, m;
  tifa_libs::fin_uint >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin_uint >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
