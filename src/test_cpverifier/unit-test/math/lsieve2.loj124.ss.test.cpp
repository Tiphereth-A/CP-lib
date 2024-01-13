#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/math/lsieve2.hpp"

#include "../../../code/math/mintdata_ss.hpp"
#include "../../../code/math/mint.hpp"
#include "../../../code/math/qpow.hpp"
#include "../base.hpp"

using mintdata = tifa_libs::math::mintdata_ss<1'000'000'000 + 7>;
using mint = tifa_libs::math::mint<mintdata>;

void test(std::string const& data) {
  std::string path = "src/data/loj/124/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  u32 n, k;
  fin >> n >> k;
  tifa_libs::math::lsieve2 ls(n);
  mint pk = 1, lst = 1;
  vec<mint> dk = ls.template run<mint>([&](u32 p, u32 e) {
    if (e == 1) pk = tifa_libs::math::qpow<mint>(p, k), lst = 1 + pk;
    else lst = lst * pk + 1;
    return lst;
  });
  mint res = 0;
  for (u32 i = 1; i <= n; ++i) res += dk[i];

  u64 got = res.val(), want;
  fans >> want;
  check(got, want, check_param(data));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00:
      test("sieve0");
      test("sieve1");
      test("sieve2");
      break;
    case tifa_libs::unittest::ts_example_01:
      test("sieve3");
      test("sieve4");
      test("sieve5");
      break;
    case tifa_libs::unittest::ts_random_00:
      test("sieve6");
      test("sieve7");
      test("sieve8");
      break;
    case tifa_libs::unittest::ts_random_01:
      test("sieve9");
      test("sieve10");
      test("sieve11");
      break;
    case tifa_libs::unittest::ts_random_02:
      test("sieve12");
      test("sieve13");
      test("sieve14");
      break;
    case tifa_libs::unittest::ts_random_03:
      test("sieve15");
      test("sieve16");
      test("sieve17");
      break;
    case tifa_libs::unittest::ts_random_04:
      test("sieve18");
      test("sieve19");
      test("sieve20");
      break;
    case tifa_libs::unittest::ts_random_05:
      test("sieve21");
      test("sieve22");
      test("sieve23");
      break;
    case tifa_libs::unittest::ts_random_06:
      test("sieve24");
      break;
    default:
      break;
  }

  tifa_libs::unittest::post_test();
}