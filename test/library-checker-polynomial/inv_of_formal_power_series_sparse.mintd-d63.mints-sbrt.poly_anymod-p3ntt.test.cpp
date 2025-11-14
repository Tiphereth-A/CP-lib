#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series_sparse"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/poly/inv_fpssp.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d63.hpp"
#include "../../include/math/mint_sbrt.hpp"
#include "../../include/poly/poly3ntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_d63, __LINE__>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_sbrt, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_sbrt, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_sbrt, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  mint::set_mod(MOD);
  u32 n, k;
  tifa_libs::fin >> n >> k;
  poly p(n);
  for (u32 i = 0, x; i < k; ++i) tifa_libs::fin >> x >> p[x];
  tifa_libs::fout << tifa_libs::math::inv_fpssp(p);
  return 0;
}
