// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_add_range_min
#include "../../../src/ds/bst/fhq_w/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
using T = i64;
using F = i64;

auto op(T a, T b) { return min(a, b); }
T e() { return inf_v<T>; }
auto mapping(F f, T a) { return a + f; }
auto composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
  u32 n, q;
  i64 x;
  fin_uint >> n >> q;
  fhq_treap_w<T, op, e, F, mapping, composition, id, true> tr(n + q);
  flt_ (u32, i, 0, n) fin_int >> x, tr.insert(x);
  for (u32 i = 0, opt, l, r; i < q; ++i) {
    fin_uint >> opt >> l >> r;
    if (!opt) fin_int >> x, tr.update(l, r - 1, x);
    else fout << tr.query(l, r - 1) << '\n';
  }
  return 0;
}
