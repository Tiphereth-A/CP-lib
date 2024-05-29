#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/nt/lsieve2.hpp"

#include "../../../code/math/mint_s30.hpp"
#include "../../../code/math/qpow.hpp"
#include "../base.hpp"

using mint = tifa_libs::math::mint_s30<1'000'000'000 + 7>;

void test(strn CR data) {
  strn path = "src/data/loj/124/sieve" + data;
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
  fle_ (u32, i, 1, n) res += dk[i];

  u64 got = res.val(), want;
  fans >> want;
  check(got, want, check_param(data));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("0"), test("12"), test("24"); break;
    case tifa_libs::unittest::ts_example_01: test("1"), test("13"); break;
    case tifa_libs::unittest::ts_random_00: test("2"), test("14"); break;
    case tifa_libs::unittest::ts_random_01: test("3"), test("15"); break;
    case tifa_libs::unittest::ts_random_02: test("4"), test("16"); break;
    case tifa_libs::unittest::ts_random_03: test("5"), test("17"); break;
    case tifa_libs::unittest::ts_random_04: test("6"), test("18"); break;
    case tifa_libs::unittest::ts_random_05: test("7"), test("19"); break;
    case tifa_libs::unittest::ts_random_06: test("8"), test("20"); break;
    case tifa_libs::unittest::ts_random_07: test("9"), test("21"); break;
    case tifa_libs::unittest::ts_random_08: test("10"), test("22"); break;
    case tifa_libs::unittest::ts_random_09: test("11"), test("23"); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}