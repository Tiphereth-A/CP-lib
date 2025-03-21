#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../../include/ds/persistent_segtree.hpp"
#include "../../include/edh/discretization.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"

int main() {
  u32 n, q;
  tifa_libs::fin >> n >> q;
  veci _(n);
  for (auto &x : _) tifa_libs::fin >> x;
  auto [b, a] = tifa_libs::gen_id(_);
  tifa_libs::ds::persistent_segtree seg(a, (u32)b.size() + 1);
  for (u32 i = 0, l, r, k; i < q; ++i) {
    tifa_libs::fin >> l >> r >> k;
    tifa_libs::fout << b[seg.kth_min(l, r - 1, k + 1)] << '\n';
  }
  return 0;
}
