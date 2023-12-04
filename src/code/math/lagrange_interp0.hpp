#ifndef TIFALIBS_MATH_LAGRANGE_INTERP0
#define TIFALIBS_MATH_LAGRANGE_INTERP0

#include "../comb/gen_ifact.hpp"
#include "mul_mod_s.hpp"
#include "mul_mod_u.hpp"

namespace tifa_libs::math {

inline i64 lagrange_interp0(vec<i64> const &v, u64 x, u64 mod, vec<u64> const &ifact) {
  u32 n = (u32)v.size();
  assert(n);
  if (n == 1) return v[0];
  if (x < n) return v[x];
  vec<u64> pre(n);
  for (u32 i = 0; i < n; ++i) pre[i] = x - i;
  for (u32 i = 1; i < n; ++i) pre[i] = mul_mod_u(pre[i], pre[i - 1], mod);
  vec<u64> suc(n);
  for (u32 i = 0; i < n; ++i) suc[i] = x - i;
  for (u32 i = n - 2; ~i; --i) suc[i] = mul_mod_u(suc[i], suc[i + 1], mod);
  i64 ans = 0;
  for (u32 i = 0; i < n; ++i) {
    i64 _ = v[i];
    if (i) _ = mul_mod_s(_, (i64)pre[i - 1], mod);
    if (i + 1 < n) _ = mul_mod_s(_, (i64)suc[i + 1], mod);
    _ = mul_mod_s(mul_mod_s(_, (i64)ifact[i], mod), (i64)ifact[n - i - 1], mod);
    ans = (ans + ((n - i) % 2 ? _ : (i64)mod - _)) % (i64)mod;
  }
  return ans;
}
inline i64 lagrange_interp0(vec<i64> const &v, u64 x, u64 mod) { return lagrange_interp0(v, x, mod, gen_ifact((u32)v.size(), mod)); }
template <class mint>
mint lagrange_interp0(vec<mint> const &v, u64 x, vec<mint> const &ifact) {
  vec<i64> _(v.size());
  for (u32 i = 0; i < (u32)v.size(); ++i) _[i] = v[i].val();
  vec<u64> ifa(ifact.size());
  for (u32 i = 0; i < (u32)ifact.size(); ++i) ifa[i] = ifact[i].val();
  return mint(lagrange_interp0(_, x, mint::mod(), ifa));
}
template <class mint>
mint lagrange_interp0(vec<mint> const &v, u64 x) { return lagrange_interp0(v, x, mint::mod(), gen_ifact<mint>(v.size())); }

}  // namespace tifa_libs::math

#endif