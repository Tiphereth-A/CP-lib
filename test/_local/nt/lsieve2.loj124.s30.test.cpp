#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/nt/lsieve2.hpp"

#include "../../../include/math/mint.hpp"
#include "../../../include/math/mint_ms.hpp"
#include "../../../include/math/qpow.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms, 1'000'000'000 + 7>;

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("loj", "124", "sieve"s + data.data());
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n, k;
  fin >> n >> k;
  math::lsieve2 ls(n);
  mint pk = 1, lst = 1;
  vec<mint> dk = ls.template run<mint>([&](u32 p, u32 e) {
    if (e == 1) pk = math::qpow<mint>(p, k), lst = 1 + pk;
    else lst = lst * pk + 1;
    return lst;
  });
  mint res = 0;
  flt_ (u32, i, 1, n + 1) res += dk[i];

  u64 got = res.val(), want;
  fans >> want;
  check(got, want, check_param(data));
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("0"), test("12"), test("24"); break;
    case unittest::TC::example_01: test("1"), test("13"); break;
    case unittest::TC::random_00: test("2"), test("14"); break;
    case unittest::TC::random_01: test("3"), test("15"); break;
    case unittest::TC::random_02: test("4"), test("16"); break;
    case unittest::TC::random_03: test("5"), test("17"); break;
    case unittest::TC::random_04: test("6"), test("18"); break;
    case unittest::TC::random_05: test("7"), test("19"); break;
    case unittest::TC::random_06: test("8"), test("20"); break;
    case unittest::TC::random_07: test("9"), test("21"); break;
    case unittest::TC::random_08: test("10"), test("22"); break;
    case unittest::TC::random_09: test("11"), test("23"); break;
    default: break;
  }

  unittest::post_test();
}