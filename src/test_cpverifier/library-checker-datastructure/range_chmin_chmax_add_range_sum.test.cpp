#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include "../../code/ds/segbeats_cmmashm.hpp"
#include "../../code/io/fastio.hpp"

int main() {
  u32 n, q;
  tifa_libs::fin >> n >> q;
  vec<i64> a(n);
  for (auto& x : a) tifa_libs::fin >> x;
  tifa_libs::ds::segbeats_cmmashm<i64> seg(a);
  for (u32 i = 0, opt, l, r; i < q; ++i) {
    tifa_libs::fin >> opt >> l >> r;
    --r;
    if (opt == 3) tifa_libs::fout << seg.querys(1, 0, n - 1, l, r) << '\n';
    else {
      i64 b;
      tifa_libs::fin >> b;
      if (opt == 0) seg.chmin(1, 0, n - 1, l, r, b);
      else if (opt == 1) seg.chmax(1, 0, n - 1, l, r, b);
      else seg.add(1, 0, n - 1, l, r, b);
    }
  }
  return 0;
}
