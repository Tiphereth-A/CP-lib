#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../code/comb/binom.hpp"
#include "../../code/comb/lucas.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_ds.hpp"
#include "../../code/util/fastio.hpp"

using mintdata = tifa_libs::math::mintdata_ds<-1>;
using mint = tifa_libs::math::mint<mintdata>;

int main() {
  u32 t, m;
  tifa_libs::fin >> t >> m;
  mintdata::set_mod(m);
  if (m < 1e7) {
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
