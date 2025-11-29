#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/ds/segbeats_ca_ms.hpp"

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
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"), test("13"); break;
    case unittest::TC::example_01: test("2"), test("14"); break;
    case unittest::TC::random_00: test("3"), test("15"); break;
    case unittest::TC::random_01: test("4"), test("16"); break;
    case unittest::TC::random_02: test("5"), test("17"); break;
    case unittest::TC::random_03: test("6"), test("18"); break;
    case unittest::TC::random_04: test("7"), test("19"); break;
    case unittest::TC::random_05: test("8"), test("20"); break;
    case unittest::TC::random_06: test("9"); break;
    case unittest::TC::random_07: test("10"); break;
    case unittest::TC::random_08: test("11"); break;
    case unittest::TC::random_09: test("12"); break;
    default: break;
  }

  unittest::post_test();
}