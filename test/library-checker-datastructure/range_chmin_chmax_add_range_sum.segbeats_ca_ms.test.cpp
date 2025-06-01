#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include "../../include/ds/segbeats_ca_ms.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/io/ios128.hpp"

using namespace tifa_libs;
int main() {
  u32 n, q;
  fin >> n >> q;
  vecii a(n);
  for (auto& i : a) fin >> i;
  ds::segbeats_ca_ms<i64, i128> seg(a);
  for (u32 i = 0, opt, l, r; i < q; ++i) {
    fin >> opt >> l >> r;
    if (opt == 3) fout << seg.query_sum(l, r) << '\n';
    else {
      i64 b;
      fin >> b;
      if (opt == 0) seg.chmin(l, r, b);
      else if (opt == 1) seg.chmax(l, r, b);
      else seg.add(l, r, b);
    }
  }
  return 0;
}
