#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include "../../code/ds/segbeats_ca_ms.hpp"
#include "../../code/io/fastio.hpp"

int main() {
  u32 n, q;
  tifa_libs::fin >> n >> q;
  vecii a(n);
  for (auto& i : a) tifa_libs::fin >> i;
  tifa_libs::ds::segbeats_ca_ms<i64, i128> seg(a);
  for (u32 i = 0, opt, l, r; i < q; ++i) {
    tifa_libs::fin >> opt >> l >> r;
    if (opt == 3) tifa_libs::fout << seg.query_sum(l, r) << '\n';
    else {
      i64 b;
      tifa_libs::fin >> b;
      if (opt == 0) seg.chmin(l, r, b);
      else if (opt == 1) seg.chmax(l, r, b);
      else seg.add(l, r, b);
    }
  }
  return 0;
}
