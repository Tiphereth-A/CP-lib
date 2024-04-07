#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/nt/period_fib.hpp"

#include "../../../code/lalg/mat.hpp"
#include "../../../code/math/mint_d31.hpp"
#include "../../../code/math/mint_ds.hpp"
#include "../../../code/math/qpow.hpp"
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

using mint1 = tifa_libs::math::mint_d31<-1>;
using mint2 = tifa_libs::math::mint_ds<-1>;

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test<mint1>(2); break;
    case tifa_libs::unittest::ts_random_00: test<mint2>(2); break;
    case tifa_libs::unittest::ts_random_01: test<mint1>(10); break;
    case tifa_libs::unittest::ts_random_02: test<mint2>(10); break;
    case tifa_libs::unittest::ts_random_03: test<mint1>(5000); break;
    case tifa_libs::unittest::ts_random_04: test<mint2>(5000); break;
    case tifa_libs::unittest::ts_random_05: test<mint1>(1919810); break;
    case tifa_libs::unittest::ts_random_06: test<mint2>(1919810); break;
    case tifa_libs::unittest::ts_random_07: test<mint1>(1'000'000'000); break;
    case tifa_libs::unittest::ts_random_08: test<mint2>(1'000'000'000); break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}