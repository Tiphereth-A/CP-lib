#ifndef TIFALIBS_MATH_CRT
#define TIFALIBS_MATH_CRT

#include "../math/safe_mod.hpp"
#include "inv_gcd.hpp"

namespace tifa_libs::math {
namespace crt_impl_ {
CEXP std::optional<ptt<i64>> crt2(i64 a0, u64 m0, i64 a1, u64 m1) {
  if (m0 < m1) return crt2(a1, m1, a0, m0);
  auto [d, x] = inv_gcd(m0, m1);
  const i64 a1_a0 = a1 - a0, a1_a0_d = a1_a0 / (i64)d;
  if (a1_a0 != a1_a0_d * (i64)d) return {};
  const i64 m1_d = (i64)(m1 / d);
  i64 k0 = (i64)x % m1_d * (a1_a0_d % m1_d) % m1_d;
  if (k0 < 0) k0 += m1_d;
  return std::make_pair(a0 + k0 * (i64)m0, (i64)m0 * m1_d);
}
}  // namespace crt_impl_

// Returns (remainder, modular)
CEXP std::optional<ptt<u64>> crt(vec<i64> CR a, vecu64 CR m) {
  if (a.size() != m.size()) return {};
  i64 A = 0;
  u64 M = 1;
  const u32 n = (u32)a.size();
  flt_ (u32, i, 0, n)
    if (auto res = crt_impl_::crt2(safe_mod(a[i], m[i]), m[i], A, M); !res) return {};
    else std::tie(A, M) = res.value();
  return std::make_pair(A, M);
}

}  // namespace tifa_libs::math

#endif