#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/edh/hamming.hpp"

#include "../base.hpp"

using namespace tifa_libs;
rand::gen<ds::dbitset::word_t> g;

void test(u64 n) {
  ds::dbitset s(n, g);

  auto v = hamming::encode(s);
  auto m = v.size() - n - 1;
  check_bool(v.size() <= (1_u64 << m), check_param(n), check_param(m), check_param(s.to_string()), check_param(v.to_string()));

  auto t = hamming::decode(v);
  check_bool(t.has_value(), check_param(s.to_string()), check_param(v.to_string()));
  check(t->to_string(), s.to_string(), check_param(v.to_string()));
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test((1 << 2) - 3), test(0), test(10); break;
    case unittest::TC::example_01: test((1 << 3) - 4), test(2), test(100); break;
    case unittest::TC::random_00: test((1 << 4) - 5), test(3), test(1000); break;
    case unittest::TC::random_01: test((1 << 5) - 6), test(5), test(10000); break;
    case unittest::TC::random_02: test((1 << 6) - 7), test(6), test(200000); break;
    case unittest::TC::random_03: test((1 << 7) - 8), test(7), test(500000); break;
    case unittest::TC::random_04: test((1 << 8) - 9), test(8), test(100000); break;
    case unittest::TC::random_05: test((1 << 9) - 10), test(9), test(200000); break;
    case unittest::TC::random_06: test((1 << 10) - 11), test(12), test(500000); break;
    case unittest::TC::random_07: test((1 << 11) - 12), test(13), test(1000000); break;
    case unittest::TC::random_08: test((1 << 12) - 13), test(14), test(2000000); break;
    case unittest::TC::random_09: test((1 << 13) - 14), test(15), test(5000000); break;
    default: break;
  }

  unittest::post_test();
}