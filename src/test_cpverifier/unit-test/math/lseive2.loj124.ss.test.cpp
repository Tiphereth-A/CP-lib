#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/math/lseive2.hpp"

#include "../../../code/math/mint_ss.hpp"
#include "../../../code/math/qpow.hpp"
#include "../base.hpp"

using mint = tifa_libs::math::mint_ss<1'000'000'000 + 7>;

void test(std::string const& data) {
  std::string path = "src/data/loj/124/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  u32 n, k;
  fin >> n >> k;
  tifa_libs::math::lseive2 ls(n);
  mint pk = 1, lst = 1;
  vec<mint> dk = ls.template run<mint>([&](u32 p, u32 e) {
    if (e == 1) pk = tifa_libs::math::qpow<mint>(p, k), lst = 1 + pk;
    else lst = lst * pk + 1;
    return lst;
  });
  mint res = 0;
  for (u32 i = 1; i <= n; ++i) res += dk[i];
  u64 got = res.val();

  u64 want;
  fans >> want;
  check(got, want, check_param(data));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00:
      test("seive0");
      test("seive1");
      test("seive2");
      break;
    case tifa_libs::unittest::ts_example_01:
      test("seive3");
      test("seive4");
      test("seive5");
      break;
    case tifa_libs::unittest::ts_random_00:
      test("seive6");
      test("seive7");
      test("seive8");
      break;
    case tifa_libs::unittest::ts_random_01:
      test("seive9");
      test("seive10");
      test("seive11");
      break;
    case tifa_libs::unittest::ts_random_02:
      test("seive12");
      test("seive13");
      test("seive14");
      break;
    case tifa_libs::unittest::ts_random_03:
      test("seive15");
      test("seive16");
      test("seive17");
      break;
    case tifa_libs::unittest::ts_random_04:
      test("seive18");
      test("seive19");
      test("seive20");
      break;
    case tifa_libs::unittest::ts_random_05:
      test("seive21");
      test("seive22");
      test("seive23");
      break;
    case tifa_libs::unittest::ts_random_06:
      test("seive24");
      break;
    default:
      break;
  }

  tifa_libs::unittest::post_test();
}