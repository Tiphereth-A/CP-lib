#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../../code/ds/persistent_segtree.hpp"
#include "../../code/util/discretization.hpp"
#include "../../code/util/fastio.hpp"

int main() {
  usz n, q;
  tifa_libs::fin >> n >> q;
  vec<i32> _(n);
  for (auto &x : _) tifa_libs::fin >> x;
  auto [b, a] = tifa_libs::gen_id(_);
  tifa_libs::ds::persistent_segtree seg(a, b.size() + 1);
  for (usz i = 0, l, r, k; i < q; ++i) {
    tifa_libs::fin >> l >> r >> k;
    tifa_libs::fout << b[seg.kth_min(l, r - 1, k + 1)] << '\n';
  }
  return 0;
}
