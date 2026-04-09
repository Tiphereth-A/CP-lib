// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/binomial_coefficient
#include "../../../src/comb/exlucas/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 t, m;
  fin_uint >> t >> m;
  if (m == 1) {
    while (t--) fout << "0\n";
  } else {
    exlucas mCn(m);
    while (t--) {
      i64 n, k;
      fin_uint >> n >> k;
      fout << mCn(n, k) << '\n';
    }
  }
  return 0;
}
