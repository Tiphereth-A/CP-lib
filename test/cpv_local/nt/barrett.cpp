// competitive-verifier: STANDALONE

#include "../../../src/nt/mod/barrett/lib.hpp"
#include "../../../src/util/rand/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;

decltype(default_timer.passed()) cnt_brt, cnt_bf;
rand_gen<u32> gen_a;
void single_test(u64 b, u32 mod, auto brt) {
  flt_ (u32, i, 0, 10000) {
    u32 a = gen_a() % mod;
    default_timer.tic(__LINE__);
    auto got = brt.reduce(a);
    default_timer.tac();
    cnt_brt += default_timer.passed();
    default_timer.tic(__LINE__);
    auto want = a * b % mod;
    default_timer.tac();
    cnt_bf += default_timer.passed();
    check(got, want, check_param(a), check_param(b), check_param(mod));
  }
}

void test(u32 mod) {
  flt_ (u64, b, 0, 100) {
    barrett<0> brt(mod, b);
    single_test(b, mod, brt);
  }
  std::cerr << std::format("Barrett: {}, BF: {}\n", cnt_brt, cnt_bf);
}

template <u32 MOD, u64 B>
void test_s() {
#define _(I)                      \
  {                               \
    barrett<MOD, B + I> brt;      \
    single_test(B + I, MOD, brt); \
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
  timer_(test(2));
  timer_(test(3));
  timer_(test(998244353));
  timer_(test(114514));
  timer_(test(1919810));
  timer_(test(1000000000 + 7));
  timer_(test_s<2, 0>());
  timer_(test_s<3, 0>());
  timer_(test_s<114514, 0>());
  timer_(test_s<998244353, 0>());
  timer_(test_s<1000000000 + 7, 0>());
  timer_(test_s<2, 1>());
  timer_(test_s<3, 1>());
  timer_(test_s<114514, 1>());
  timer_(test_s<998244353, 1>());
  timer_(test_s<1000000000 + 7, 1>());
  timer_(test_s<2, 2>());
  timer_(test_s<3, 2>());
  timer_(test_s<114514, 2>());
  timer_(test_s<998244353, 2>());
  timer_(test_s<1000000000 + 7, 2>());
  timer_(test_s<2, 3>());
  timer_(test_s<3, 3>());
  timer_(test_s<114514, 3>());
  timer_(test_s<998244353, 3>());
  timer_(test_s<1000000000 + 7, 3>());
  timer_(test_s<2, 4>());
  timer_(test_s<3, 4>());
  timer_(test_s<114514, 4>());
  timer_(test_s<998244353, 4>());
  timer_(test_s<1000000000 + 7, 4>());
  timer_(test_s<2, 5>());
  timer_(test_s<3, 5>());
  timer_(test_s<114514, 5>());
  timer_(test_s<998244353, 5>());
  timer_(test_s<1000000000 + 7, 5>());
  timer_(test_s<2, 6>());
  timer_(test_s<3, 6>());
  timer_(test_s<114514, 6>());
  timer_(test_s<998244353, 6>());
  timer_(test_s<1000000000 + 7, 6>());
  timer_(test_s<2, 7>());
  timer_(test_s<3, 7>());
  timer_(test_s<114514, 7>());
  timer_(test_s<998244353, 7>());
  timer_(test_s<1000000000 + 7, 7>());
  timer_(test_s<2, 8>());
  timer_(test_s<3, 8>());
  timer_(test_s<114514, 8>());
  timer_(test_s<998244353, 8>());
  timer_(test_s<1000000000 + 7, 8>());
  timer_(test_s<2, 9>());
  timer_(test_s<3, 9>());
  timer_(test_s<114514, 9>());
  timer_(test_s<998244353, 9>());
  timer_(test_s<1000000000 + 7, 9>());
}