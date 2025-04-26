#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

// clang-format off
#include "../../../include/util/pair_op.hpp"
// clang-format on

#include "../../../include/nt/lsieve2.hpp"

#include "../../../include/math/mint.hpp"
#include "../../../include/math/mint_s30.hpp"
#include "../base.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_s30, 998244353>;

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("loj", "6680", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n;
  fin >> n;
  tifa_libs::math::lsieve2 ls(n);
  ptt<mint> lst;
  vecpt<mint> g = ls.run([&](u32 p, u32 e) {
    if (e == 1) return lst = ptt<mint>(p + (p ^ 1), 1 + (p ^ 1));
    else return lst = ptt<mint>((lst.first * p + (p ^ e)), (lst.second + (p ^ e)));
  },
                         ptt<mint>{1, 1});

  vec<mint> f(n + 1);
  f[1] = 1;
  flt_ (u32, i, 2, n + 1) f[i] = f[i - 1] + g[i].first + g[i].first - g[i].second;
  u64 got = f[1].val();
  flt_ (u32, i, 2, n + 1) got ^= f[i].val();

  u64 want;
  fans >> want;
  check(got, want, check_param(data));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"), test("13"); break;
    case tifa_libs::unittest::ts_example_01: test("2"), test("14"); break;
    case tifa_libs::unittest::ts_random_00: test("3"), test("15"); break;
    case tifa_libs::unittest::ts_random_01: test("4"), test("16"); break;
    case tifa_libs::unittest::ts_random_02: test("5"), test("17"); break;
    case tifa_libs::unittest::ts_random_03: test("6"), test("18"); break;
    case tifa_libs::unittest::ts_random_04: test("7"), test("19"); break;
    case tifa_libs::unittest::ts_random_05: test("8"), test("20"); break;
    case tifa_libs::unittest::ts_random_06: test("9"); break;
    case tifa_libs::unittest::ts_random_07: test("10"); break;
    case tifa_libs::unittest::ts_random_08: test("11"); break;
    case tifa_libs::unittest::ts_random_09: test("12"); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}