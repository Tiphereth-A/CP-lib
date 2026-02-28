#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_composite_set_power_series"

#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/sps/comp/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_bs, MOD>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;

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
