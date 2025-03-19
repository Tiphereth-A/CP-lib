#ifndef TIFALIBS_MATH_LAGRANGE_INTERP0
#define TIFALIBS_MATH_LAGRANGE_INTERP0

#include "../comb/gen_ifact.hpp"
#include "mul_mod.hpp"

namespace tifa_libs::math {

CEXP i64 lagrange_interp0(spnii v, u64 x, u64 mod, spnuu ifact) NE {
  const u32 n = (u32)v.size();
  if (assert(n); n == 1) return v[0];
  if (x < n) return v[x];
  vecuu pre(n);
  flt_ (u32, i, 0, n) pre[i] = x - i;
  flt_ (u32, i, 1, n) pre[i] = mul_mod_u(pre[i], pre[i - 1], mod);
  vecuu suc(n);
  flt_ (u32, i, 0, n) suc[i] = x - i;
  for (u32 i = n - 2; ~i; --i) suc[i] = mul_mod_u(suc[i], suc[i + 1], mod);
  i64 ans = 0;
  flt_ (u32, i, 0, n) {
    i64 _ = v[i];
    if (i) _ = mul_mod_s(_, (i64)pre[i - 1], mod);
    if (i + 1 < n) _ = mul_mod_s(_, (i64)suc[i + 1], mod);
    _ = mul_mod_s(mul_mod_s(_, (i64)ifact[i], mod), (i64)ifact[n - i - 1], mod);
    ans = (ans + ((n - i) % 2 ? _ : (i64)mod - _)) % (i64)mod;
  }
  return ans;
}
CEXP i64 lagrange_interp0(spnii v, u64 x, u64 mod) NE { return lagrange_interp0(v, x, mod, gen_ifact((u32)v.size(), mod)); }
template <class mint>
CEXP mint lagrange_interp0(vec<mint> CR v, u64 x, vec<mint> CR ifact) NE {
  vecii _(v.size());
  flt_ (u32, i, 0, (u32)v.size()) _[i] = (i64)v[i].val();
  vecuu ifa(ifact.size());
  flt_ (u32, i, 0, (u32)ifact.size()) ifa[i] = ifact[i].val();
  return mint(lagrange_interp0(_, x, mint::mod(), ifa));
}
template <class mint>
CEXP mint lagrange_interp0(vec<mint> CR v, u64 x) NE { return lagrange_interp0(v, x, mint::mod(), gen_ifact<mint>(v.size())); }

}  // namespace tifa_libs::math

#endif