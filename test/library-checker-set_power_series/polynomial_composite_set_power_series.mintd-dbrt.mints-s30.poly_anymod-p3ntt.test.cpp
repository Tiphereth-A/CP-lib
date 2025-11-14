#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_composite_set_power_series"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/poly/comp_fpssps.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_dbrt.hpp"
#include "../../include/math/mint_s30.hpp"
#include "../../include/poly/poly3ntt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_dbrt, __LINE__>;
using namespace tifa_libs;
using mint_p3ntt1 = math::mint<math::mint_s30, 167772161>;
using mint_p3ntt2 = math::mint<math::mint_s30, 469762049>;
using mint_p3ntt3 = math::mint<math::mint_s30, 754974721>;
using poly = math::poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  mint::set_mod(MOD);
  u32 m, n;
  tifa_libs::fin >> m >> n;
  poly a(m);
  tifa_libs::fin >> a;
  vec<mint> b(1 << n);
  for (auto &i : b) tifa_libs::fin >> i;
  tifa_libs::fout << tifa_libs::math::comp_fpssps(n, a, b) << '\n';
  return 0;
}
