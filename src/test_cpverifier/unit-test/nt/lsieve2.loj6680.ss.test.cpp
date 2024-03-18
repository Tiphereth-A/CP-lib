#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

// clang-format off
#include "../../../code/util/pair_op.hpp"
// clang-format on

#include "../../../code/nt/lsieve2.hpp"
#include "../../../code/math/mint_ss.hpp"
#include "../base.hpp"

using mint = tifa_libs::math::mint_ss<998244353>;


void test(strn const& data) {
  strn path = "src/data/loj/6680/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  u32 n;
  fin >> n;
  tifa_libs::math::lsieve2 ls(n);
  ptt<mint> lst;
  vec<ptt<mint>> g = ls.run([&](u32 p, u32 e) {
    if (e == 1) return lst = ptt<mint>(p + (p ^ 1), 1 + (p ^ 1));
    else return lst = ptt<mint>((lst.first * p + (p ^ e)), (lst.second + (p ^ e)));
  },
                            ptt<mint>{1, 1});

  vec<mint> f(n + 1);
  f[1] = 1;
  for (u32 i = 2; i <= n; ++i) f[i] = f[i - 1] + g[i].first + g[i].first - g[i].second;
  u64 got = f[1].val();
  for (u32 i = 2; i <= n; ++i) got ^= f[i].val();

  u64 want;
  fans >> want;
  check(got, want, check_param(data));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00:
      test("1");
      test("2");
      break;
    case tifa_libs::unittest::ts_example_01:
      test("3");
      test("4");
      break;
    case tifa_libs::unittest::ts_random_00:
      test("5");
      test("6");
      break;
    case tifa_libs::unittest::ts_random_01:
      test("7");
      test("8");
      break;
    case tifa_libs::unittest::ts_random_02:
      test("9");
      test("10");
      break;
    case tifa_libs::unittest::ts_random_03:
      test("11");
      test("12");
      break;
    case tifa_libs::unittest::ts_random_04:
      test("13");
      test("14");
      break;
    case tifa_libs::unittest::ts_random_05:
      test("15");
      test("16");
      break;
    case tifa_libs::unittest::ts_random_06:
      test("17");
      test("18");
      break;
    case tifa_libs::unittest::ts_random_07:
      test("19");
      test("20");
      break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}