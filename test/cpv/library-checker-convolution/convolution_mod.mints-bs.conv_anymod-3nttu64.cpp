#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/conv/add/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = mint_bs<MOD>;
using namespace tifa_libs;
using mint_3nttu640 = mint_bs<167772161>;
using mint_3nttu641 = mint_bs<469762049>;
using mint_3nttu642 = mint_bs<754974721>;
using ntt_3nttu640_t = ntt<mint_3nttu640>;
using ntt_3nttu641_t = ntt<mint_3nttu641>;
using ntt_3nttu642_t = ntt<mint_3nttu642>;
using vec_t = vecuu;
auto conv_func(vec_t CR a, vec_t CR b) {
  ntt_3nttu640_t ntt0;
  ntt_3nttu641_t ntt1;
  ntt_3nttu642_t ntt2;
  return conv_3ntt_u64(ntt0, ntt1, ntt2, a, b, MOD);
}

int main() {
  u32 n, m;
  tifa_libs::fin_uint >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin_uint >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
