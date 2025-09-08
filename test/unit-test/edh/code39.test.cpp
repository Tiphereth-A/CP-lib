#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/edh/code39.hpp"

#include "../base.hpp"

using namespace tifa_libs;
rand::gen<char> g(0, 127);
rand::gen<u32> g2(0, 43);

void test(u32 n) {
  strn s(n, '\0');
  for (auto& c : s) c = g();
  auto v = code39::encode<true>(s);
  auto d10 = code39::check_digit<false>(v), d43 = code39::check_digit<true>(v);
  strn t = code39::decode<true>(v);
  check(t, s, check_param(d10), check_param(d43), check_param(v));

  strn s2(n, '\0');
  for (auto& c : s2) c = code39::alphabet[g2()];
  auto v2 = code39::encode(s2);
  auto d10_2 = code39::check_digit<false>(v2), d43_2 = code39::check_digit<true>(v2);
  strn t2 = code39::decode(v2);
  check(t2, s2, check_param(d10_2), check_param(d43_2), check_param(v2));
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