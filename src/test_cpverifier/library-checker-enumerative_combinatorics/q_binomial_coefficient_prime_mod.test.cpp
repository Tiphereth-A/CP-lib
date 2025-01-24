#define PROBLEM "https://judge.yosupo.jp/problem/q_binomial_coefficient_prime_mod"

#include "../../code/comb/qbinom.hpp"
#include "../../code/io/fastio.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;

int main() {
  u32 t, MOD, q;
  tifa_libs::fin >> t >> MOD >> q;
  mint::set_mod(MOD);
  if (!q) {
    while (t--) {
      i64 n, k;
      tifa_libs::fin >> n >> k;
      tifa_libs::fout << !(n < k || k < 0) << '\n';
    }
    return 0;
  }
  tifa_libs::math::qbinom<mint> mCn(q);
  while (t--) {
    i64 n, k;
    tifa_libs::fin >> n >> k;
    tifa_libs::fout << mCn.qmCn(n, k) << '\n';
  }

  return 0;
}
