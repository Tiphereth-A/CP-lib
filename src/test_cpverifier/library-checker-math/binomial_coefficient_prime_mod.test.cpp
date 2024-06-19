#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../code/comb/binom.hpp"
#include "../../code/io/fastio.hpp"
#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint_d31<-1>;

int main() {
  u32 t, MOD;
  tifa_libs::fin >> t >> MOD;
  mint::set_mod(MOD);
  tifa_libs::math::Binom<mint> mCn(10'000'001);
  while (t--) {
    i64 n, k;
    tifa_libs::fin >> n >> k;
    tifa_libs::fout << (MOD < 1e7 ? mCn.lucas(n, k) : mCn.mCn(n, k)) << '\n';
  }
  return 0;
}
