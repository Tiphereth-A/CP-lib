#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"

#include "../../code/comb/exlucas.hpp"
#include "../../code/util/fastio.hpp"

int main() {
  u32 t, m;
  tifa_libs::fin >> t >> m;
  if (m == 1) {
    while (t--) tifa_libs::fout << "0\n";
  } else {
    tifa_libs::math::ExLucas mCn(m);
    while (t--) {
      i64 n, k;
      tifa_libs::fin >> n >> k;
      tifa_libs::fout << mCn(n, k) << '\n';
    }
  }
  return 0;
}
