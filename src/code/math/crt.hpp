#ifndef TIFA_LIBS_MATH_CRT
#define TIFA_LIBS_MATH_CRT

#include "inv_gcd.hpp"
#include "safe_mod.hpp"

namespace tifa_libs::math {

namespace crt_impl_ {

constexpr std::optional<std::pair<i64, i64>> crt2(i64 a0, u64 m0, i64 a1, u64 m1) {
  if (m0 < m1) return crt2(a1, m1, a0, m0);
  auto [d, x] = inv_gcd(m0, m1);
  i64 a1_a0 = a1 - a0;
  i64 a1_a0_d = a1_a0 / (i64)d;
  if (a1_a0 != a1_a0_d * (i64)d) return {};
  i64 m1_d = (i64)(m1 / d), k0 = (i64)x % m1_d * (a1_a0_d % m1_d) % m1_d;
  if (k0 < 0) k0 += m1_d;
  return std::make_pair((u64)(a0 + k0 * (i64)m0), m0 * (u64)m1_d);
}

}  // namespace crt_impl_

// Returns (remainder, modular)
inline std::optional<std::pair<u64, u64>> crt(const vec<i64> &a, const vec<u64> &m) {
  if (a.size() != m.size()) return {};
  const usz n = a.size();
  i64 A = 0;
  u64 M = 1;
  for (usz i = 0; i < n; ++i) {
    auto res = crt_impl_::crt2(safe_mod(a[i], m[i]), m[i], A, M);
    if (!res) return {};
    std::tie(A, M) = res.value();
  }
  return std::make_pair(A, M);
}

}  // namespace tifa_libs::math

#endif