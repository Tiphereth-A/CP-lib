#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/math/barrett.hpp"

#include "../base.hpp"

using namespace tifa_libs;

decltype(unittest::default_timer.passed()) cnt_brt, cnt_bf;
rand::gen<u32> gen_a;
void single_test(u64 b, u32 mod, auto brt) {
  flt_ (u32, i, 0, 10000) {
    u32 a = gen_a() % mod;
    unittest::default_timer.tic(__LINE__);
    auto got = brt.reduce(a);
    unittest::default_timer.tac();
    cnt_brt += unittest::default_timer.passed();
    unittest::default_timer.tic(__LINE__);
    auto want = u32(a * b % mod);
    unittest::default_timer.tac();
    cnt_bf += unittest::default_timer.passed();
    check(got, want, check_param(a), check_param(b), check_param(mod));
  }
}

void test(u32 mod) {
  flt_ (u64, b, 0, 100) {
    math::barrett<0> brt(mod, b);
    single_test(b, mod, brt);
  }
  std::cerr << std::format("Barrett: {}, BF: {}\n", cnt_brt, cnt_bf);
}

template <u32 MOD, u64 B>
void test_s() {
#define _(I)                       \
  {                                \
    math::barrett<MOD, B + I> brt; \
    single_test(B + I, MOD, brt);  \
  }
  _(0)
  _(10)
  _(42)
  _(114514)
  _(1919810)
  _(19260817)
  _(998244353)
  _((1_u64 << 32))
#undef _
  std::cerr << std::format("Barrett: {}, BF: {}\n", cnt_brt, cnt_bf);
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test(2), test(3), test(998244353); break;
    case unittest::TC::example_01: test(114514), test(1919810), test(1000000000 + 7); break;
    case unittest::TC::random_00: test_s<2, 0>(), test_s<3, 0>(), test_s<114514, 0>(), test_s<998244353, 0>(), test_s<1000000000 + 7, 0>(); break;
    case unittest::TC::random_01: test_s<2, 1>(), test_s<3, 1>(), test_s<114514, 1>(), test_s<998244353, 1>(), test_s<1000000000 + 7, 1>(); break;
    case unittest::TC::random_02: test_s<2, 2>(), test_s<3, 2>(), test_s<114514, 2>(), test_s<998244353, 2>(), test_s<1000000000 + 7, 2>(); break;
    case unittest::TC::random_03: test_s<2, 3>(), test_s<3, 3>(), test_s<114514, 3>(), test_s<998244353, 3>(), test_s<1000000000 + 7, 3>(); break;
    case unittest::TC::random_04: test_s<2, 4>(), test_s<3, 4>(), test_s<114514, 4>(), test_s<998244353, 4>(), test_s<1000000000 + 7, 4>(); break;
    case unittest::TC::random_05: test_s<2, 5>(), test_s<3, 5>(), test_s<114514, 5>(), test_s<998244353, 5>(), test_s<1000000000 + 7, 5>(); break;
    case unittest::TC::random_06: test_s<2, 6>(), test_s<3, 6>(), test_s<114514, 6>(), test_s<998244353, 6>(), test_s<1000000000 + 7, 6>(); break;
    case unittest::TC::random_07: test_s<2, 7>(), test_s<3, 7>(), test_s<114514, 7>(), test_s<998244353, 7>(), test_s<1000000000 + 7, 7>(); break;
    case unittest::TC::random_08: test_s<2, 8>(), test_s<3, 8>(), test_s<114514, 8>(), test_s<998244353, 8>(), test_s<1000000000 + 7, 8>(); break;
    case unittest::TC::random_09: test_s<2, 9>(), test_s<3, 9>(), test_s<114514, 9>(), test_s<998244353, 9>(), test_s<1000000000 + 7, 9>(); break;
    default: break;
  }

  unittest::post_test();
}