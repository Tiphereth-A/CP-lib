#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/nt/lsieve2.hpp"

#include "../base.hpp"

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "4804", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t;
  fin >> t;
  vecu ns(t);
  flt_ (u32, i, 0, t) fin >> ns[i];

  u32 n = std::ranges::max(ns);
  tifa_libs::math::lsieve2 ls(n);
  u64 lst = 1;
  vecuu g = ls.template run<u64>([&](u32 p, u32 e) {
    if (e == 1) return lst = p - 2;
    else if (e == 2) return lst = u64(p - 1) * (p - 1);
    else return lst *= p;
  });
  vecuu f(n + 1);
  flt_ (u32, i, 1, n + 1) f[i] = f[i - 1] + g[i];

  for (u32 n : ns) {
    u64 got = 0;
    for (u32 l = 1, r, d; l <= n; l = r + 1) r = n / (d = n / l), got += (f[r] - f[l - 1]) * d * d;

    u64 want;
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
    case tifa_libs::unittest::ts_random_03: break;
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