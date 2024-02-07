#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/nt/lsieve2.hpp"

#include "../../../code/math/mint.hpp"
#include "../../../code/math/mintdata_s30.hpp"
#include "../../../code/math/qpow.hpp"
#include "../base.hpp"

using mintdata = tifa_libs::math::mintdata_s30<1'000'000'000 + 7>;
using mint = tifa_libs::math::mint<mintdata>;

void test(strn const& data) {
  strn path = "src/data/bzoj/4407/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  u32 t, k;
  fin >> t >> k;
  vec<u32> ns(t), ms(t);
  for (u32 i = 0; i < t; ++i) {
    fin >> ns[i] >> ms[i];
    if (ns[i] > ms[i]) std::swap(ns[i], ms[i]);
  }
  u32 n = *std::max_element(ns.begin(), ns.end());
  tifa_libs::math::lsieve2 ls(n);
  static mint pk, lst;
  vec<mint> g = ls.template run<mint>(
      [&](u32 p, u32 e) {
        if (e == 1) return lst = (pk = tifa_libs::math::qpow<mint>(p, k)) - 1;
        else return lst *= pk;
      });
  std::partial_sum(g.begin(), g.end(), g.begin());
  for (u32 i = 0; i < t; ++i) {
    mint res = 0;
    for (u32 n = ns[i], m = ms[i], l = 1, r, d1, d2; l <= n; l = r + 1) {
      r = std::min(n / (d1 = n / l), m / (d2 = m / l));
      res += (g[r] - g[l - 1]) * d1 * d2;
    }

    u64 got = res.val(), want;
    fans >> want;
    check(got, want, check_param(data));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: test("2"); break;
    case tifa_libs::unittest::ts_random_00: test("3"); break;
    case tifa_libs::unittest::ts_random_01: test("4"); break;
    case tifa_libs::unittest::ts_random_02: test("5"); break;
    case tifa_libs::unittest::ts_random_03: test("6"); break;
    case tifa_libs::unittest::ts_random_04: test("7"); break;
    case tifa_libs::unittest::ts_random_05: test("8"); break;
    case tifa_libs::unittest::ts_random_06: test("9"); break;
    case tifa_libs::unittest::ts_random_07: test("10"); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}