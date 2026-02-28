// competitive-verifier: STANDALONE

#include "../../../src/ds/segtree/segbeats_ca_ms/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "4695", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n;
  fin >> n;
  vecii a(n);
  for (auto& i : a) fin >> i;
  ds::segbeats_ca_ms<i64> seg(a);
  u32 q;
  fin >> q;
  for (u32 i = 0, tp, l, r; i < q; ++i) {
    fin >> tp >> l >> r;
    if (tp < 4) {
      i64 x;
      fin >> x;
      if (tp == 1) seg.add(l - 1, r, x);
      else if (tp == 2) seg.chmax(l - 1, r, x);
      else if (tp == 3) seg.chmin(l - 1, r, x);
    } else {
      i64 got;
      if (tp == 4) got = seg.query_sum(l - 1, r);
      else if (tp == 5) got = seg.query_max(l - 1, r);
      else if (tp == 6) got = seg.query_min(l - 1, r);
      else check_bool(0, check_param(data), check_param(i), check_param(tp), check_param(l), check_param(r));
      i64 want;
      fans >> want;
      check(got, want, check_param(data), check_param(i), check_param(tp), check_param(l), check_param(r));
    }
  }
}

int main() {
  for (int i = 1; i <= 20; ++i) {
    timer_(test(std::to_string(i)));
  }
}