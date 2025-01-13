#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/ds/fhq_treap.hpp"

#include "../base.hpp"

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "3224", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n;
  fin >> n;
  tifa_libs::ds::fhq_treap<i32> treap;
  for (u32 i = 0, opt; i < n; ++i) {
    i32 x, got, want;
    fin >> opt >> x;
    switch (opt) {
      case 1:
        treap.insert(x);
        break;
      case 2:
        treap.erase(x);
        break;
      case 3:
        got = (int)treap.rank(x);
        fans >> want;
        break;
      case 4:
        got = treap.kth((u32)x).value();
        fans >> want;
        break;
      case 5:
        got = treap.prev(x).value();
        fans >> want;
        break;
      case 6:
        got = treap.next(x).value();
        fans >> want;
        break;
    }
    check(got, want, check_param(i), check_param(opt), check_param(x));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: test("2"); break;
    case tifa_libs::unittest::ts_random_00: test("3"); break;
    case tifa_libs::unittest::ts_random_01: test("4"); break;
    case tifa_libs::unittest::ts_random_02: test("5"); break;
    case tifa_libs::unittest::ts_random_03: test("6"); break;
    case tifa_libs::unittest::ts_random_04: test("7"); break;
    case tifa_libs::unittest::ts_random_05: test("8"); break;
    case tifa_libs::unittest::ts_random_06: test("9"); break;
    case tifa_libs::unittest::ts_random_07: test("10"); break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}