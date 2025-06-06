#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/conv/conv_3ntt.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s30.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, MOD>;
using namespace tifa_libs;
using mint_3ntt0 = math::mint<math::mint_s30, 167772161>;
using mint_3ntt1 = math::mint<math::mint_s30, 469762049>;
using mint_3ntt2 = math::mint<math::mint_s30, 754974721>;
using ntt_3ntt0_t = math::NTT<mint_3ntt0>;
using ntt_3ntt1_t = math::NTT<mint_3ntt1>;
using ntt_3ntt2_t = math::NTT<mint_3ntt2>;
using vec_t = vec<mint>;
auto conv_func(vec_t CR a, vec_t CR b) {
  ntt_3ntt0_t ntt0;
  ntt_3ntt1_t ntt1;
  ntt_3ntt2_t ntt2;
  return math::conv_3ntt(ntt0, ntt1, ntt2, a, b);
}

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
