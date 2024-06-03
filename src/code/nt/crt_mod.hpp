#ifndef TIFALIBS_MATH_CRT_MOD
#define TIFALIBS_MATH_CRT_MOD

#include "../math/safe_mod.hpp"
#include "gcd.hpp"
#include "inverse.hpp"

namespace tifa_libs::math {

CEXP std::optional<pttu> crt_mod(spni a, vecu m, u32 const mod) {
  if (a.size() != m.size()) return {};
  const u32 n = (u32)a.size();
  flt_ (u32, i, 0, n) {
    u32 &mi = m[i];
    flt_ (u32, j, 0, i) {
      u32 &mj = m[j], d = gcd(mi, mj);
      if (d == 1) continue;
      if (safe_mod(a[i], d) != safe_mod(a[j], d)) return {};
      mi /= d, mj /= d;
      if (u32 k = gcd(mi, d); k != 1)
        while (d % k == 0) mi *= k, d /= k;
      mj *= d;
    }
  }
  m.push_back(mod);
  veci pp(n + 1, 1), res(n + 1);
  flt_ (u32, i, 0, n) {
    const i64 u = safe_mod((safe_mod(a[i], m[i]) - res[i]) * (i64)inverse((u64)pp[i], m[i]), m[i]);
    fle_ (u32, j, i + 1, n) res[j] = (i32)((res[j] + u * pp[j]) % m[j]), pp[j] = (i32)((i64)pp[j] * m[i] % m[j]);
  }
  return std::make_pair(res.back(), pp.back());
}

}  // namespace tifa_libs::math

#endif