#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/math/mint.hpp"
#include "../../../include/math/mint_ms.hpp"
#include "../../../include/math/mint_ms64.hpp"
#include "../../../include/poly/asin_fps.hpp"
#include "../../../include/poly/atan_fps.hpp"
#include "../../../include/poly/cossin_fps.hpp"
#include "../../../include/poly/polyntt.hpp"
#include "../base.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;
using mints30 = math::mint<math::mint_ms, MOD>;
using mints63 = math::mint<math::mint_ms64, MOD>;

using pnm30 = math::polyntt<mints30>;
using pnm63 = math::polyntt<mints63>;

rand::gen<u64> gen;

template <class poly>
void test(u32 n) {
  using mint = TPN poly::val_t;
  poly p(n + 1);
  p[0] = 0;
  flt_ (u32, i, 1, n + 1) p[i] = mint(gen());
  const u32 sz = n + 1;

  auto sqrt_1mpp = math::sqrt_fps(-p * p + 1, sz).value();
  auto sqrt_1app = math::sqrt_fps(p * p + 1, sz).value();
  auto inv_sqrt_1app = math::inv_fps(sqrt_1app);
  auto p_inv_sqrt_1app = (p * inv_sqrt_1app).pre(sz);

  timer_(auto [p_cos, p_sin] = math::cossin_fps(p));
  timer_(auto p_asin = math::asin_fps(p));
  timer_(auto p_atan = math::atan_fps(p));

  check(math::asin_fps(-p), -p_asin, check_param(p));
  check(math::atan_fps(-p), -p_atan, check_param(p));

  auto [p_cos_asin, p_sin_asin] = math::cossin_fps(p_asin);
  check(p_cos_asin, sqrt_1mpp, check_param(p), check_param(p_asin));
  check(p_sin_asin, p, check_param(p_asin));

  auto [p_cos_atan, p_sin_atan] = math::cossin_fps(p_atan);
  check(p_cos_atan, inv_sqrt_1app, check_param(p), check_param(p_atan));
  check(p_sin_atan, p_inv_sqrt_1app, check_param(p), check_param(p_atan), check_param(inv_sqrt_1app));
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test<pnm30>(100); break;
    case unittest::TC::random_00: test<pnm63>(100); break;
    case unittest::TC::random_01: test<pnm30>(1000); break;
    case unittest::TC::random_02: test<pnm63>(1000); break;
    case unittest::TC::random_03: test<pnm30>(100000); break;
    case unittest::TC::random_04: test<pnm63>(100000); break;
    case unittest::TC::random_05: break;
    case unittest::TC::random_06: break;
    case unittest::TC::random_07: break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}