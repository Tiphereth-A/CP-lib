#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series_sparse"

#include "../../../src/fpssp/pow/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"
#include "../../../src/math/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md, __LINE__>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_bs, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_bs, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_bs, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  mint::set_mod(MOD);
  u32 n, k;
  u64 m;
  tifa_libs::fin_uint >> n >> k >> m;
  poly p(n);
  for (u32 i = 0, x; i < k; ++i) tifa_libs::fin_uint >> x >> p[x];
  tifa_libs::fout << tifa_libs::math::pow_fpssp(p, m);
  return 0;
}
