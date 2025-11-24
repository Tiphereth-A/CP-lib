#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"

#include "../../include/comb/exlucas.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"

using namespace tifa_libs;
int main() {
  u32 t, m;
  fin_uint >> t >> m;
  if (m == 1) {
    while (t--) fout << "0\n";
  } else {
    math::exlucas mCn(m);
    while (t--) {
      i64 n, k;
      fin_uint >> n >> k;
      fout << mCn(n, k) << '\n';
    }
  }
  return 0;
}
