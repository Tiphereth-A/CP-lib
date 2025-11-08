#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/edh/hamming.hpp"

#include "../base.hpp"

using namespace tifa_libs;
rand::gen<ds::dbitset::word_t> g;

void test(u64 n) {
  ds::dbitset s(n, g);

  timer_(auto v = hamming::encode(s));
  auto m = v.size() - n - 1;
  check_bool(v.size() <= (1_u64 << m), check_param(n), check_param(m), check_param(s.to_string()), check_param(v.to_string()));

  timer_(auto t = hamming::decode(v));
  check_bool(t.has_value(), check_param(s.to_string()), check_param(v.to_string()));
  check(t->to_string(), s.to_string(), check_param(v.to_string()));
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00:
      flt_ (u32, i, 2, 10) test((1 << i) - (i + 1));
      break;
    case unittest::TC::example_01:
      flt_ (u32, i, 0, 20) test(i);
      break;
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