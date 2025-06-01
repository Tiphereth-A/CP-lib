#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multivariate_convolution"

#include "../../include/conv/conv_mval_dft.hpp"
#include "../../include/conv/ntt.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s63, MOD>;

using ntt_t = tifa_libs::math::NTT<mint>;
using vec_t = vec<mint>;

int main() {
  u32 k, n = 1;
  tifa_libs::fin >> k;
  vecu base(k);
  for (auto &i : base) tifa_libs::fin >> i, n *= i;
  vec_t a(n), b(n);
  tifa_libs::fin >> a >> b;
  ntt_t ntt;
  tifa_libs::fout << tifa_libs::math::conv_mval_dft(ntt, a, b, base) << '\n';
  return 0;
}
