#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include "../../code/io/fastio.hpp"
#include "../../code/nt/exbsgs.hpp"

int main() {
  i64 t;
  tifa_libs::fin >> t;
  while (t--) {
    u64 x, y, m;
    tifa_libs::fin >> x >> y >> m;
    auto res = tifa_libs::math::exbsgs(x, y, m);
    tifa_libs::fout << (res ? (i64)res.value() : -1) << '\n';
  }
  return 0;
}
