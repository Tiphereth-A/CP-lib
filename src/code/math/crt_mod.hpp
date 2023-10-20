#ifndef TIFA_LIBS_MATH_CRT_MOD
#define TIFA_LIBS_MATH_CRT_MOD

#include "inverse.hpp"
#include "safe_mod.hpp"

namespace tifa_libs::math {

inline std::optional<std::pair<u32, u32>> crt_mod(const vec<i32> &a, const vec<u32> &m, const u32 mod) {
  if (a.size() != m.size()) return {};
  const usz n = a.size();
  vec<u32> m_cpy(m);
  for (usz i = 0; i < n; ++i) {
    u32 &mi = m_cpy[i];
    for (usz j = 0; j < i; ++j) {
      u32 &mj = m_cpy[j], d = std::gcd(mi, mj);
      if (d == 1) continue;
      if (safe_mod(a[i], d) != safe_mod(a[j], d)) return {};
      mi /= d;
      mj /= d;
      if (u32 k = std::gcd(mi, d); k != 1)
        while (d % k == 0) {
          mi *= k;
          d /= k;
        }
      mj *= d;
    }
  }
  m_cpy.push_back(mod);
  vec<i32> pp(n + 1, 1), res(n + 1);
  for (usz i = 0; i < n; ++i) {
    i64 u = safe_mod((safe_mod(a[i], m_cpy[i]) - res[i]) * (i64)inverse((u64)pp[i], m_cpy[i]), m_cpy[i]);
    for (usz j = i + 1; j <= n; ++j) {
      res[j] = (i32)((res[j] + u * pp[j]) % m_cpy[j]);
      pp[j] = (i32)((i64)pp[j] * m_cpy[i] % m_cpy[j]);
    }
  }
  return std::make_pair(res.back(), pp.back());
}

}  // namespace tifa_libs::math

#endif