#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/math/mint_s30.hpp"
#include "../../../code/math/mint_s63.hpp"
#include "../../../code/math/mint_ss.hpp"
#include "../../../code/poly/asin_fps.hpp"
#include "../../../code/poly/atan_fps.hpp"
#include "../../../code/poly/cossin_fps.hpp"
#include "../../../code/poly/polyntt.hpp"
#include "../base.hpp"

CEXP u32 MOD = 998244353;
using mints30 = tifa_libs::math::mint_s30<MOD>;
using mints63 = tifa_libs::math::mint_s63<MOD>;
using mintss = tifa_libs::math::mint_ss<MOD>;

using pnm30 = tifa_libs::math::polyntt<mints30>;
using pnm63 = tifa_libs::math::polyntt<mints63>;
using pnms = tifa_libs::math::polyntt<mintss>;

tifa_libs::rand::Gen<std::uniform_int_distribution<u64>> gen;

template <class poly>
void test(u32 n) {
  using mint = TPN poly::value_type;
  poly p(n + 1);
  p[0] = 0;
  fle_(u32, i, 1, n) p[i] = mint(gen());
  const u32 sz = n + 1;

  auto sqrt_1mpp = tifa_libs::math::sqrt_fps(-p * p + 1, sz).value();
  auto sqrt_1app = tifa_libs::math::sqrt_fps(p * p + 1, sz).value();
  auto inv_sqrt_1app = tifa_libs::math::inv_fps(sqrt_1app);
  auto p_inv_sqrt_1app = (p * inv_sqrt_1app).pre(sz);

  auto [p_cos, p_sin] = tifa_libs::math::cossin_fps(p);
  auto p_asin = tifa_libs::math::asin_fps(p);
  auto p_atan = tifa_libs::math::atan_fps(p);

  check(tifa_libs::math::asin_fps(-p), -p_asin, check_param(p));
  check(tifa_libs::math::atan_fps(-p), -p_atan, check_param(p));

  auto [p_cos_asin, p_sin_asin] = tifa_libs::math::cossin_fps(p_asin);
  check(p_cos_asin, sqrt_1mpp, check_param(p), check_param(p_asin));
  check(p_sin_asin, p, check_param(p_asin));

  auto [p_cos_atan, p_sin_atan] = tifa_libs::math::cossin_fps(p_atan);
  check(p_cos_atan, inv_sqrt_1app, check_param(p), check_param(p_atan));
  check(p_sin_atan, p_inv_sqrt_1app, check_param(p), check_param(p_atan), check_param(inv_sqrt_1app));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test<pnm30>(100); break;
    case tifa_libs::unittest::ts_random_00: test<pnm63>(100); break;
    case tifa_libs::unittest::ts_random_01: test<pnms>(100); break;
    case tifa_libs::unittest::ts_random_02: test<pnm30>(1000); break;
    case tifa_libs::unittest::ts_random_03: test<pnm63>(1000); break;
    case tifa_libs::unittest::ts_random_04: test<pnms>(1000); break;
    case tifa_libs::unittest::ts_random_05: test<pnm30>(100000); break;
    case tifa_libs::unittest::ts_random_06: test<pnm63>(100000); break;
    case tifa_libs::unittest::ts_random_07: test<pnms>(100000); break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}