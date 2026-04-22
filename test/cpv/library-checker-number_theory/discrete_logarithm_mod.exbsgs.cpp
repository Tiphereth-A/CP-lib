// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/discrete_logarithm_mod
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/nt/dlog/bsgs/lib.hpp"
#include "../../../src/nt/dlog/exbsgs/lib.hpp"

using namespace tifa_libs;
int main() {
  i64 t;
  fin_uint >> t;
  while (t--) {
    u64 x, y, m;
    fin_uint >> x >> y >> m;
    auto res = exbsgs(bsgs, x, y, m);
    fout << (res ? (i64)res.value() : -1) << '\n';
  }
  return 0;
}
