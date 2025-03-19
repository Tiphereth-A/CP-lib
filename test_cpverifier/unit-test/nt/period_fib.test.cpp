#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/nt/period_fib.hpp"

#include "../../../include/lalg/mat.hpp"
#include "../../../include/math/mint.hpp"
#include "../../../include/math/mint_d31.hpp"
#include "../../../include/math/qpow.hpp"
#include "../base.hpp"

template <class mint>
void test(u32 n) {
  mint::set_mod(n);
  u64 period = tifa_libs::math::period_fib(n);
  tifa_libs::math::matrix<mint> a(2, 2), b(2, 1), i(2, 2);
  a(0, 1) = a(1, 0) = a(1, 1) = 1;
  b(1, 0) = 1;
  i(0, 0) = i(1, 1) = 1;
  a = tifa_libs::math::qpow(a, period, i);
  check(a * b, b, check_param(n), check_param(period), check_param(a));
}

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test<mint>(2); break;
    case tifa_libs::unittest::ts_random_00: test<mint>(10); break;
    case tifa_libs::unittest::ts_random_01: test<mint>(5000); break;
    case tifa_libs::unittest::ts_random_02: test<mint>(1919810); break;
    case tifa_libs::unittest::ts_random_03: test<mint>(1'000'000'000); break;
    case tifa_libs::unittest::ts_random_04: break;
    case tifa_libs::unittest::ts_random_05: break;
    case tifa_libs::unittest::ts_random_06: break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}