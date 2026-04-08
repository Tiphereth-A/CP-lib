#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series_sparse"

#include "../../../src/fpssp/ln/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = mint_bs<MOD>;
using namespace tifa_libs;
using poly = polymtt<mint>;

int main() {
  u32 n, k;
  tifa_libs::fin_uint >> n >> k;
  poly p(n);
  for (u32 i = 0, x; i < k; ++i) tifa_libs::fin_uint >> x >> p[x];
  tifa_libs::fout << tifa_libs::ln_fpssp(p);
  return 0;
}
