#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "../../../src/io/container/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/math/ssts_pim_cnt/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt/lib.hpp"
#include "../../../src/math/ds/mint/ms/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms<MOD>;
using namespace tifa_libs;
using poly = polyntt<mint>;

int main() {
  u32 n, t;
  tifa_libs::fin_uint >> n >> t;
  vecu s(n);
  tifa_libs::fin_uint >> s;
  auto v = tifa_libs::ssts_pim_cnt<poly>(s, t);
  flt_ (u32, i, 1, t + 1) tifa_libs::fout << v[i] << " \n"[i == t];
  return 0;
}
