#ifndef TIFALIBS_MATH_CRT
#define TIFALIBS_MATH_CRT

#include "../math/safe_mod.hpp"
#include "inv_gcd.hpp"

namespace tifa_libs::math {
namespace crt_impl_ {
CEXP auto crt2(i64 a0, u64 m0, i64 a1, u64 m1) NE {
  std::optional<pttii> ret;
  if (m0 < m1) swap(a0, a1), swap(m0, m1);
  auto [d, x] = inv_gcd(m0, m1);
  const i64 a1_a0 = a1 - a0, a1_a0_d = a1_a0 / (i64)d;
  if (a1_a0 != a1_a0_d * (i64)d) return ret;
  const i64 m1_d = (i64)(m1 / d);
  i64 k0 = (i64)x % m1_d * (a1_a0_d % m1_d) % m1_d;
  if (k0 < 0) k0 += m1_d;
  ret.emplace(a0 + k0 * (i64)m0, (i64)m0 * m1_d);
  return ret;
}
}  // namespace crt_impl_

// Returns (remainder, modular)
CEXP auto crt(spnii a, spnuu m) NE {
  std::optional<pttuu> ret;
  if (a.size() != m.size()) return ret;
  ret.emplace(0, 1);
  const u32 n = (u32)a.size();
  flt_ (u32, i, 0, n)
    if (ret = crt_impl_::crt2(safe_mod(a[i], m[i]), m[i], (i64)ret->first, ret->second); !ret) return ret;
  return ret;
}

}  // namespace tifa_libs::math

#endif