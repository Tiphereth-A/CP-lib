#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_composite_set_power_series"

#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/sps/comp/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"
#include "../../../src/math/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms, MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_ms64, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_ms64, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_ms64, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  u32 m, n;
  tifa_libs::fin_uint >> m >> n;
  poly a(m);
  tifa_libs::fin_uint >> a;
  vec<mint> b(1 << n);
  for (auto& i : b) tifa_libs::fin_uint >> i;
  tifa_libs::fout << tifa_libs::math::comp_fpssps(n, a, b) << '\n';
  return 0;
}
