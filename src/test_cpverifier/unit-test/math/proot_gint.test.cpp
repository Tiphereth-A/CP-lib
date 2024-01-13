#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/math/proot_gint.hpp"

#include "../../../code/math/jacobi_sym.hpp"
#include "../../../code/math/mint.hpp"
#include "../../../code/math/mintdata_s63.hpp"
#include "../../../code/math/mintdata_ss.hpp"
#include "../../../code/math/qpow.hpp"
#include "../base.hpp"

template <u32 MOD>
using mint = tifa_libs::math::mint<tifa_libs::math::mintdata_ss<MOD>>;
template <u64 MOD>
using mint64 = tifa_libs::math::mintdata_s63<MOD>;

template <class mint, i64 M>
void __single_test(decltype(mint::mod()) mod, vec<decltype(mint::mod())> const& pf_v) {
  mint mint_M = mint{M};
  using gint = tifa_libs::math::GaussInt<mint, M>;
  if (mint_M.val() <= 1) return;
  gint g = tifa_libs::math::proot_gint<mint, M>();
  check_bool(g.real() == 1, check_param(g));
  gint g_qpow = tifa_libs::math::qpow(g, mod + 1);

  if (tifa_libs::math::jacobi_sym(mint_M.val(), mod) == -1) {
    gint g_mp1{1 - g.imag() * g.imag() * mint_M, 0};
    check_bool(g_qpow == g_mp1, check_param(g), check_param(g_qpow), check_param(g_mp1), check_param(mod), check_param(pf_v));
  } else {
    gint g_mp1{1 + g.imag() * g.imag() * mint_M, g.imag() * 2};
    check_bool(g_qpow == g_mp1, check_param(g), check_param(g_qpow), check_param(g_mp1), check_param(mod), check_param(pf_v));
  }
}

template <class mint>
void test_proot_gint() {
  auto mod = mint::mod();
  auto pf = tifa_libs::math::pfactors(mod - 1);
  vec<decltype(mod)> pf_v;
  pf_v.reserve(pf.size());
  for (auto [k, v] : pf) pf_v.push_back((decltype(mod))k);

  __single_test<mint, 2>(mod, pf_v);
  __single_test<mint, 3>(mod, pf_v);
  __single_test<mint, 5>(mod, pf_v);
  __single_test<mint, 7>(mod, pf_v);
  __single_test<mint, 11>(mod, pf_v);

  __single_test<mint, -1>(mod, pf_v);
  __single_test<mint, -2>(mod, pf_v);
  __single_test<mint, -3>(mod, pf_v);
  __single_test<mint, -5>(mod, pf_v);
  __single_test<mint, -7>(mod, pf_v);
  __single_test<mint, -11>(mod, pf_v);
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
      // small prime
    case tifa_libs::unittest::ts_example_00:
      test_proot_gint<mint<2>>();
      test_proot_gint<mint<3>>();
      test_proot_gint<mint<5>>();
      test_proot_gint<mint<7>>();
      test_proot_gint<mint<11>>();
      test_proot_gint<mint<13>>();
      test_proot_gint<mint<17>>();
      test_proot_gint<mint<19>>();
      test_proot_gint<mint<40961>>();
      test_proot_gint<mint<65537>>();
      test_proot_gint<mint<786433>>();
      test_proot_gint<mint<19260817>>();
      break;
      // larger prime in u32
    case tifa_libs::unittest::ts_example_01:
      test_proot_gint<mint<167772161>>();
      test_proot_gint<mint<469762049>>();
      test_proot_gint<mint<754974721>>();
      test_proot_gint<mint<998244353>>();
      test_proot_gint<mint<999292927>>();
      test_proot_gint<mint<1000000007>>();
      test_proot_gint<mint<1004535809>>();
      test_proot_gint<mint<2013265921>>();
      break;
      // larger prime in u64
    case tifa_libs::unittest::ts_random_00:
      test_proot_gint<mint64<75161927681>>();
      test_proot_gint<mint64<77309411329>>();
      test_proot_gint<mint64<2061584302081>>();
      test_proot_gint<mint64<6597069766657>>();
      test_proot_gint<mint64<1231453023109121>>();
      test_proot_gint<mint64<3799912185593857>>();
      test_proot_gint<mint64<180143985094819841>>();
      test_proot_gint<mint64<4179340454199820289>>();
      break;
    default:
      break;
  }

  tifa_libs::unittest::post_test();
}