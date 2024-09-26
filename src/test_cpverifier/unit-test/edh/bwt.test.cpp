#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/edh/bwt.hpp"

#include "../../../code/edh/bwt_inv.hpp"
#include "../base.hpp"

tifa_libs::rand::Gen<char> g('\x21', '\x7f');

void test(u32 n) {
  strn s(n+1, '\x20');
  fle_(u32, i, 1, n) s[i] = g();
  strn bwt_s = tifa_libs::bwt(s);
  strn bwt_inv_s = tifa_libs::bwt_inv(bwt_s);
  check(bwt_inv_s, s, check_param(bwt_s));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test(10); break;
    case tifa_libs::unittest::ts_example_01: test(20); break;
    case tifa_libs::unittest::ts_random_00: test(50); break;
    case tifa_libs::unittest::ts_random_01: test(100); break;
    case tifa_libs::unittest::ts_random_02: test(2000); break;
    case tifa_libs::unittest::ts_random_03: test(5000); break;
    case tifa_libs::unittest::ts_random_04: test(1000); break;
    case tifa_libs::unittest::ts_random_05: test(2000); break;
    case tifa_libs::unittest::ts_random_06: test(5000); break;
    case tifa_libs::unittest::ts_random_07: test(10000); break;
    case tifa_libs::unittest::ts_random_08: test(20000); break;
    case tifa_libs::unittest::ts_random_09: test(50000); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}