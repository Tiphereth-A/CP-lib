#ifndef TIFA_LIBS_MATH_LAGRANGE_INTERP0
#define TIFA_LIBS_MATH_LAGRANGE_INTERP0

#include "../comb/ifact_mod_gen.hpp"
#include "mul_mod_s.hpp"
#include "mul_mod_u.hpp"

namespace tifa_libs::math {

inline i64 lagrange_interp0(vec<i64> const &v, u64 x, u64 mod, vec<u64> const &ifact) {
  usz n = v.size();
  assert(n);
  if (n == 1) return v[0];
  if (x < n) return v[x];
  vec<u64> pre(n);
  for (usz i = 0; i < n; ++i) pre[i] = x - i;
  for (usz i = 1; i < n; ++i) pre[i] = mul_mod_u(pre[i], pre[i - 1], mod);
  vec<u64> suc(n);
  for (usz i = 0; i < n; ++i) suc[i] = x - i;
  for (usz i = n - 2; ~i; --i) suc[i] = mul_mod_u(suc[i], suc[i + 1], mod);
  i64 ans = 0;
  for (usz i = 0; i < n; ++i) {
    i64 _ = v[i];
    if (i) _ = mul_mod_s(_, (i64)pre[i - 1], mod);
    if (i + 1 < n) _ = mul_mod_s(_, (i64)suc[i + 1], mod);
    _ = mul_mod_s(mul_mod_s(_, (i64)ifact[i], mod), (i64)ifact[n - i - 1], mod);
    ans = (ans + ((n - i) % 2 ? _ : (i64)mod - _)) % (i64)mod;
  }
  return ans;
}
inline i64 lagrange_interp0(vec<i64> const &v, u64 x, u64 mod) { return lagrange_interp0(v, x, mod, ifact_mod_gen(v.size(), mod)); }

}  // namespace tifa_libs::math

#endif