#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/nt/exbsgs.hpp"

using namespace tifa_libs;
int main() {
  i64 t;
  fin_uint >> t;
  while (t--) {
    u64 x, y, m;
    fin_uint >> x >> y >> m;
    auto res = math::exbsgs(x, y, m);
    fout << (res ? (i64)res.value() : -1) << '\n';
  }
  return 0;
}
