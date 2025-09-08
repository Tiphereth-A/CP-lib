#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/nt/lsieve2.hpp"

#include "../../../include/math/mint.hpp"
#include "../../../include/math/mint_s30.hpp"
#include "../../../include/math/qpow.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, 1'000'000'000 + 7>;

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "4407", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t, k;
  fin >> t >> k;
  vecu ns(t), ms(t);
  flt_ (u32, i, 0, t) {
    fin >> ns[i] >> ms[i];
    if (ns[i] > ms[i]) std::swap(ns[i], ms[i]);
  }
  u32 n = std::ranges::max(ns);
  math::lsieve2 ls(n);
  static mint pk, lst;
  vec<mint> g = ls.template run<mint>(
      [&](u32 p, u32 e) -> mint {
        if (e == 1) return lst = (pk = math::qpow<mint>(p, k)) - 1;
        else return lst *= pk;
      });
  std::inclusive_scan(begin(g), end(g), begin(g));
  flt_ (u32, i, 0, t) {
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
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"); break;
    case unittest::TC::example_01: test("2"); break;
    case unittest::TC::random_00: test("3"); break;
    case unittest::TC::random_01: test("4"); break;
    case unittest::TC::random_02: test("5"); break;
    case unittest::TC::random_03: test("6"); break;
    case unittest::TC::random_04: test("7"); break;
    case unittest::TC::random_05: test("8"); break;
    case unittest::TC::random_06: test("9"); break;
    case unittest::TC::random_07: test("10"); break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}