#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/q_binomial_coefficient_prime_mod"

#include "../../../src/comb/qbinom/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/mtt/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/fact/helper_l/lib.hpp"
#include "../../../src/math/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md, __LINE__>;
using namespace tifa_libs;
using poly = math::polymtt<mint>;
using namespace tifa_libs;
using fact_t = math::factl_helper<poly>;

int main() {
  mint::set_mod(MOD);
  u32 t, mod, q;
  tifa_libs::fin_uint >> t >> mod >> q;
  mint::set_mod(mod);
  if (!q) {
    while (t--) {
      i64 n, k;
      tifa_libs::fin_uint >> n >> k;
      tifa_libs::fout << !(n < k || k < 0) << '\n';
    }
    return 0;
  }
  tifa_libs::math::qbinom<mint, fact_t> mCn(q);
  while (t--) {
    i64 n, k;
    tifa_libs::fin_uint >> n >> k;
    tifa_libs::fout << mCn.qmCn(n, k) << '\n';
  }

  return 0;
}
