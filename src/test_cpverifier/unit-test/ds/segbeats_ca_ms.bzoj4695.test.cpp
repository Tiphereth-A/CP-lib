#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/ds/segbeats_ca_ms.hpp"

#include "../base.hpp"

void test(strn CR data) {
  strn path = "src/data/bzoj/4695/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  u32 n;
  fin >> n;
  vec<i64> a(n);
  for (auto& i : a) fin >> i;
  tifa_libs::ds::segbeats_ca_ms<i64> seg(a);
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
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"), test("2"); break;
    case tifa_libs::unittest::ts_example_01: test("3"), test("4"); break;
    case tifa_libs::unittest::ts_random_00: test("5"), test("6"); break;
    case tifa_libs::unittest::ts_random_01: test("7"), test("8"); break;
    case tifa_libs::unittest::ts_random_02: test("9"), test("10"); break;
    case tifa_libs::unittest::ts_random_03: test("11"), test("12"); break;
    case tifa_libs::unittest::ts_random_04: test("13"), test("14"); break;
    case tifa_libs::unittest::ts_random_05: test("15"), test("16"); break;
    case tifa_libs::unittest::ts_random_06: test("17"); break;
    case tifa_libs::unittest::ts_random_07: test("18"); break;
    case tifa_libs::unittest::ts_random_08: test("19"); break;
    case tifa_libs::unittest::ts_random_09: test("20"); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}