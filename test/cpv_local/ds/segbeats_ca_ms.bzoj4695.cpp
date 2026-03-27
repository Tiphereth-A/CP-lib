// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/4695

#include "../../../src/ds/segtree/segbeats_ca_ms/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
int main() {
  u32 n;
  cin >> n;
  vecii a(n);
  for (auto& i : a) cin >> i;
  ds::segbeats_ca_ms<i64> seg(a);
  u32 q;
  cin >> q;
  for (u32 i = 0, tp, l, r; i < q; ++i) {
    cin >> tp >> l >> r;
    if (tp < 4) {
      i64 x;
      cin >> x;
      if (tp == 1) seg.add(l - 1, r, x);
      else if (tp == 2) seg.chmax(l - 1, r, x);
      else if (tp == 3) seg.chmin(l - 1, r, x);
    } else {
      i64 got;
      if (tp == 4) got = seg.query_sum(l - 1, r);
      else if (tp == 5) got = seg.query_max(l - 1, r);
      else got = seg.query_min(l - 1, r);
      cout << got << '\n';
    }
  }
}