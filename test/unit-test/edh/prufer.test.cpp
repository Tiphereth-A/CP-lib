#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/edh/prufer.hpp"

#include "../../../include/edh/prufer_inv.hpp"
#include "../base.hpp"

using namespace tifa_libs;

void test(u32 n) {
  rand::gen<u32> g(1, n);
  vecu seq(n - 1);
  flt_ (u32, i, 1, n - 1) seq[i] = g();
  timer_(auto tree_seq = prufer_inv(seq));
  timer_(auto prufer_seq = prufer(tree_seq));
  check(prufer_seq, seq, check_param(tree_seq));
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test(10); break;
    case unittest::TC::example_01: test(100); break;
    case unittest::TC::random_00: test(1000); break;
    case unittest::TC::random_01: test(10000); break;
    case unittest::TC::random_02: test(200000); break;
    case unittest::TC::random_03: test(500000); break;
    case unittest::TC::random_04: test(100000); break;
    case unittest::TC::random_05: test(200000); break;
    case unittest::TC::random_06: test(500000); break;
    case unittest::TC::random_07: test(1000000); break;
    case unittest::TC::random_08: test(2000000); break;
    case unittest::TC::random_09: test(5000000); break;
    default: break;
  }

  unittest::post_test();
}