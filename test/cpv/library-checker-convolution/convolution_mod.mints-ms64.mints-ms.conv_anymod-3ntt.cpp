#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/conv/add/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"
#include "../../../src/math/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms64, MOD>;
using namespace tifa_libs;
using mint_3ntt0 = math::mint<math::mint_ms, 167772161>;
using mint_3ntt1 = math::mint<math::mint_ms, 469762049>;
using mint_3ntt2 = math::mint<math::mint_ms, 754974721>;
using ntt_3ntt0_t = math::ntt<mint_3ntt0>;
using ntt_3ntt1_t = math::ntt<mint_3ntt1>;
using ntt_3ntt2_t = math::ntt<mint_3ntt2>;
using vec_t = vec<mint>;
auto conv_func(vec_t CR a, vec_t CR b) {
  ntt_3ntt0_t ntt0;
  ntt_3ntt1_t ntt1;
  ntt_3ntt2_t ntt2;
  return math::conv_3ntt(ntt0, ntt1, ntt2, a, b);
}

int main() {
  u32 n, m;
  tifa_libs::fin_uint >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin_uint >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
