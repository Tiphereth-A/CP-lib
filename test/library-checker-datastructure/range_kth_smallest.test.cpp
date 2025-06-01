#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../../include/ds/persistent_segtree.hpp"
#include "../../include/edh/discretization.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"

using namespace tifa_libs;
int main() {
  u32 n, q;
  fin >> n >> q;
  veci _(n);
  for (auto &x : _) fin >> x;
  auto [b, a] = gen_id(_);
  ds::persistent_segtree seg(a, (u32)b.size() + 1);
  for (u32 i = 0, l, r, k; i < q; ++i) {
    fin >> l >> r >> k;
    fout << b[seg.kth_min(l, r - 1, k + 1)] << '\n';
  }
  return 0;
}
