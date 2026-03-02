// competitive-verifier: STANDALONE

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"
#include "../../../src/math/mint/ms64/lib.hpp"
#include "../../../src/math/qpow/basic/lib.hpp"
#include "../../../src/nt/proot/gint/lib.hpp"
#include "../../../src/nt/residue/jacobi/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
template <u32 MOD>
using mint = math::mint<math::mint_ms, MOD>;
template <u64 MOD>
using mint64 = math::mint<math::mint_ms64, MOD>;

template <class mint, i64 M>
void __single_test(decltype(mint::mod()) mod, vec<decltype(mint::mod())> CR pf_v) {
  mint mint_M = mint{M};
  using gint = math::gint<mint, M>;
  if (mint_M.val() <= 1) return;
  timer_(gint g = math::proot_gint<mint, M>());
  check_bool(g.real() == 1, check_param(g));
  gint g_qpow = math::qpow(g, mod + 1);

  if (~math::jacobi_sym(mint_M.val(), mod)) {
    gint g_mp1{1 + g.imag() * g.imag() * mint_M, g.imag() * 2};
    check_bool(g_qpow == g_mp1, check_param(g), check_param(g_qpow), check_param(g_mp1), check_param(mod), check_param(pf_v));
  } else {
    gint g_mp1{1 - g.imag() * g.imag() * mint_M, 0};
    check_bool(g_qpow == g_mp1, check_param(g), check_param(g_qpow), check_param(g_mp1), check_param(mod), check_param(pf_v));
  }
}

template <class mint>
void test_proot_gint() {
  auto mod = mint::mod();
  auto pf = math::pfactors(mod - 1);
  vec<decltype(mod)> pf_v;
  pf_v.reserve(pf.size());
  for (auto k : pf) pf_v.push_back((decltype(mod))k);

  __single_test<mint, 2>(mod, pf_v);
  if CEXP (mint::mod() > 3) __single_test<mint, 3>(mod, pf_v);
  if CEXP (mint::mod() > 5) __single_test<mint, 5>(mod, pf_v);
  if CEXP (mint::mod() > 7) __single_test<mint, 7>(mod, pf_v);
  if CEXP (mint::mod() > 11) __single_test<mint, 11>(mod, pf_v);

  __single_test<mint, -1>(mod, pf_v);
  __single_test<mint, -2>(mod, pf_v);
  if CEXP (mint::mod() > 3) __single_test<mint, -3>(mod, pf_v);
  if CEXP (mint::mod() > 5) __single_test<mint, -5>(mod, pf_v);
  if CEXP (mint::mod() > 7) __single_test<mint, -7>(mod, pf_v);
  if CEXP (mint::mod() > 11) __single_test<mint, -11>(mod, pf_v);
}

int main() {
  // small prime
  timer_(test_proot_gint<mint<3>>());
  timer_(test_proot_gint<mint<5>>());
  timer_(test_proot_gint<mint<7>>());
  timer_(test_proot_gint<mint<11>>());
  timer_(test_proot_gint<mint<13>>());
  timer_(test_proot_gint<mint<17>>());
  timer_(test_proot_gint<mint<19>>());
  timer_(test_proot_gint<mint<40961>>());
  timer_(test_proot_gint<mint<65537>>());
  timer_(test_proot_gint<mint<786433>>());
  timer_(test_proot_gint<mint<19260817>>());
  // larger prime in u32
  timer_(test_proot_gint<mint<167772161>>());
  timer_(test_proot_gint<mint<469762049>>());
  timer_(test_proot_gint<mint<754974721>>());
  timer_(test_proot_gint<mint<998244353>>());
  timer_(test_proot_gint<mint<999292927>>());
  timer_(test_proot_gint<mint<1000000007>>());
  timer_(test_proot_gint<mint<1004535809>>());
  timer_(test_proot_gint<mint64<2013265921>>());
  timer_(test_proot_gint<mint64<75161927681>>());
  timer_(test_proot_gint<mint64<77309411329>>());
  // larger prime in u64
  timer_(test_proot_gint<mint64<2061584302081>>());
  timer_(test_proot_gint<mint64<6597069766657>>());
  timer_(test_proot_gint<mint64<1231453023109121>>());
  timer_(test_proot_gint<mint64<3799912185593857>>());
  timer_(test_proot_gint<mint64<180143985094819841>>());
  timer_(test_proot_gint<mint64<4179340454199820289>>());
}