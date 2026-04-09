// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_kth_smallest
#include "../../../src/ds/segtree/persistent/lib.hpp"
#include "../../../src/edh/discretization/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 n, q;
  fin_uint >> n >> q;
  veci _(n);
  for (auto& x : _) fin_int >> x;
  auto [b, a] = gen_id(_);
  persistent_segtree seg(a, (u32)b.size() + 1);
  for (u32 i = 0, l, r, k; i < q; ++i) {
    fin_uint >> l >> r >> k;
    fout << b[seg.kth_min(l, r - 1, k + 1)] << '\n';
  }
  return 0;
}
