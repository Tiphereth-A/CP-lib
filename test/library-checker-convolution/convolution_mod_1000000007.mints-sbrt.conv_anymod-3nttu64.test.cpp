#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 1000000007;

#include "../../include/conv/conv_3ntt.hpp"
#include "../../include/math/mint.hpp"
#include "../../include/math/mint_sbrt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_sbrt, MOD>;
using namespace tifa_libs;
using mint_3nttu640 = math::mint<math::mint_sbrt, 167772161>;
using mint_3nttu641 = math::mint<math::mint_sbrt, 469762049>;
using mint_3nttu642 = math::mint<math::mint_sbrt, 754974721>;
using ntt_3nttu640_t = math::ntt<mint_3nttu640>;
using ntt_3nttu641_t = math::ntt<mint_3nttu641>;
using ntt_3nttu642_t = math::ntt<mint_3nttu642>;
using vec_t = vecuu;
auto conv_func(vec_t CR a, vec_t CR b) {
  ntt_3nttu640_t ntt0;
  ntt_3nttu641_t ntt1;
  ntt_3nttu642_t ntt2;
  return math::conv_3ntt_u64(ntt0, ntt1, ntt2, a, b, MOD);
}

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  vec_t a(n), b(m);
  tifa_libs::fin >> a >> b;
  tifa_libs::fout << conv_func(a, b) << '\n';
  return 0;
}
