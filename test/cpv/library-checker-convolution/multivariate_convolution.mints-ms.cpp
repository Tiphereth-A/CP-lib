#define AUTO_GENERATED
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/multivariate_convolution
#include "../../../src/conv/add/mval_dft/lib.hpp"
#include "../../../src/conv/trans/ntt/lib.hpp"
#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/ms/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms<MOD>;

using ntt_t = tifa_libs::ntt<mint>;
using vec_t = vec<mint>;

int main() {
  u32 k, n = 1;
  tifa_libs::fin_uint >> k;
  vecu base(k);
  for (auto& i : base) tifa_libs::fin_uint >> i, n *= i;
  vec_t a(n), b(n);
  tifa_libs::fin_uint >> a >> b;
  ntt_t ntt;
  tifa_libs::fout << tifa_libs::conv_mval_dft(ntt, a, b, base) << '\n';
  return 0;
}
