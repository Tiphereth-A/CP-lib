#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/math/proot_gint.hpp"

#include "../../../code/math/is_proot.hpp"
#include "../../../code/math/mint_s63.hpp"
#include "../../../code/math/mint_ss.hpp"
#include "../../../code/math/qpow.hpp"
#include "../../../code/math/qresidue.hpp"
#include "../base.hpp"

template <u32 MOD>
using mint = tifa_libs::math::mint_ss<MOD>;
template <u64 MOD>
using mint64 = tifa_libs::math::mint_s63<MOD>;

template <class mint, i64 M>
void __single_test(decltype(mint::mod()) mod, vec<decltype(mint::mod())> const& pf_v) {
  mint mint_M = mint{M};
  if (mint_M.val() <= 1) return;
  auto g = tifa_libs::math::proot_gint<mint, M>();
  check_bool(g.real() == 1, check_param(g));

  auto qres = tifa_libs::math::qresidue(mint_M.val(), mod);
  if (!qres.has_value()) {
    auto norm_g = (1 + g.imag() * g.imag() * tifa_libs::math::qpow(mint_M, (mod + 1) / 2)).val();
    check_bool(tifa_libs::math::is_proot(norm_g, mod, pf_v.begin(), pf_v.end()), check_param(g), check_param(norm_g), check_param(mod), check_param(pf_v));
  } else {
    auto g_zm = (1 + g.imag() * qres.value()).val();
    check_bool(tifa_libs::math::is_proot(g_zm, mod, pf_v.begin(), pf_v.end()), check_param(g), check_param(g_zm), check_param(mod), check_param(pf_v));
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
  tifa_libs::unittest::pre_test();

  // small prime

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

  // larger prime in u32

  test_proot_gint<mint<167772161>>();
  test_proot_gint<mint<469762049>>();
  test_proot_gint<mint<754974721>>();
  test_proot_gint<mint<998244353>>();
  test_proot_gint<mint<999292927>>();
  test_proot_gint<mint<1000000007>>();
  test_proot_gint<mint<1004535809>>();
  test_proot_gint<mint<2013265921>>();

  // larger prime in u64

  test_proot_gint<mint64<75161927681>>();
  test_proot_gint<mint64<77309411329>>();
  test_proot_gint<mint64<2061584302081>>();
  test_proot_gint<mint64<6597069766657>>();
  test_proot_gint<mint64<1231453023109121>>();
  test_proot_gint<mint64<3799912185593857>>();
  test_proot_gint<mint64<180143985094819841>>();
  test_proot_gint<mint64<4179340454199820289>>();

  tifa_libs::unittest::post_test();
}