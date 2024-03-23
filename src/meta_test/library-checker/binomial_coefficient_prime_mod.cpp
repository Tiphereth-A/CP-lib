#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../code/comb/binom.hpp"
#include "../../code/comb/lucas.hpp"
#include "../../code/io/fastio.hpp"

#ifdef GENTC_d31
#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
#endif
#ifdef GENTC_ds
#include "../../code/math/mint_ds.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
#endif

int main() {
  u32 t, MOD;
  tifa_libs::fin >> t >> MOD;
#ifdef GENTC_d31
  mint::set_mod(MOD);
#endif
#ifdef GENTC_ds
  mint::set_mod(MOD);
#endif
  if (MOD < 1e7) {
    tifa_libs::math::Lucas<mint> mCn;
    while (t--) {
      i64 n, k;
      tifa_libs::fin >> n >> k;
      tifa_libs::fout << mCn(n, k) << '\n';
    }
  } else {
    tifa_libs::math::Binom<mint> mCn(10'000'001);
    while (t--) {
      i64 n, k;
      tifa_libs::fin >> n >> k;
      tifa_libs::fout << mCn.mCn(n, k) << '\n';
    }
  }
  return 0;
}
