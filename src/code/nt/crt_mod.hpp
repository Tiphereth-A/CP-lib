#ifndef TIFALIBS_MATH_CRT_MOD
#define TIFALIBS_MATH_CRT_MOD

#include "../math/safe_mod.hpp"
#include "gcd.hpp"
#include "inverse.hpp"

namespace tifa_libs::math {

CEXP std::optional<ptt<u32>> crt_mod(vec<i32> CR a, vecu CR m, u32 const mod) {
  if (a.size() != m.size()) return {};
  vecu m_cpy(m);
  const u32 n = (u32)a.size();
  flt_ (u32, i, 0, n) {
    u32 &mi = m_cpy[i];
    flt_ (u32, j, 0, i) {
      u32 &mj = m_cpy[j], d = gcd(mi, mj);
      if (d == 1) continue;
      if (safe_mod(a[i], d) != safe_mod(a[j], d)) return {};
      mi /= d, mj /= d;
      if (u32 k = gcd(mi, d); k != 1)
        while (d % k == 0) mi *= k, d /= k;
      mj *= d;
    }
  }
  m_cpy.push_back(mod);
  vec<i32> pp(n + 1, 1), res(n + 1);
  flt_ (u32, i, 0, n) {
    const i64 u = safe_mod((safe_mod(a[i], m_cpy[i]) - res[i]) * (i64)inverse((u64)pp[i], m_cpy[i]), m_cpy[i]);
    fle_ (u32, j, i + 1, n) res[j] = (i32)((res[j] + u * pp[j]) % m_cpy[j]), pp[j] = (i32)((i64)pp[j] * m_cpy[i] % m_cpy[j]);
  }
  return std::make_pair(res.back(), pp.back());
}

}  // namespace tifa_libs::math

#endif