#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../code/comb/lucas.hpp"
#include "../../code/comb/binom.hpp"
#include "../../code/util/fastio.hpp"

int main() {
  u32 t, m;
  tifa_libs::fin >> t >> m;
  if (m < 1e7) {
    tifa_libs::math::Lucas mCn(m);
    while (t--) {
      i64 n, k;
      tifa_libs::fin >> n >> k;
      tifa_libs::fout << mCn(n, k) << '\n';
    }
  } else {
    tifa_libs::math::Binom mCn(m, 10'000'001);
    while (t--) {
      i64 n, k;
      tifa_libs::fin >> n >> k;
      tifa_libs::fout << mCn.mCn(n, k) << '\n';
    }
  }
  return 0;
}
