#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/q_binomial_coefficient_prime_mod"

#include "../../code/comb/qbinom.hpp"
#include "../../code/io/fastio.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/factl_helper.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d31.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;
using poly = tifa_libs::math::polymtt<mint>;
using fact_t = tifa_libs::math::factl_helper<poly>;

int main() {
  mint::set_mod(MOD);
  u32 t, mod, q;
  tifa_libs::fin >> t >> mod >> q;
  mint::set_mod(mod);
  if (!q) {
    while (t--) {
      i64 n, k;
      tifa_libs::fin >> n >> k;
      tifa_libs::fout << !(n < k || k < 0) << '\n';
    }
    return 0;
  }
  tifa_libs::math::qbinom<mint, fact_t> mCn(q);
  while (t--) {
    i64 n, k;
    tifa_libs::fin >> n >> k;
    tifa_libs::fout << mCn.qmCn(n, k) << '\n';
  }

  return 0;
}
