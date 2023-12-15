#ifndef TIFALIBS_MATH_MIN_MOD_LINEAR
#define TIFALIBS_MATH_MIN_MOD_LINEAR

#include "../util/util.hpp"

namespace tifa_libs::math {

constexpr u32 min_mod_linear(u32 n, u32 m, u32 a, u32 b, u32 cnt = 1, u32 p = 1, u32 q = 1) {
  if (!a) return b;
  if (cnt & 1) {
    if (b >= a) {
      u32 t = (m - b + a - 1) / a, c = (t - 1) * p + q;
      if (n <= c) return b;
      n -= c;
      b += a * t - m;
    }
    b = a - 1 - b;
  } else {
    if (b < m - a) {
      u32 t = (m - b - 1) / a, c = t * p;
      if (n <= c) return a * ((n - 1) / p) + b;
      n -= c;
      b += a * t;
    }
    b = m - 1 - b;
  }
  u32 d = m / a, c = min_mod_linear(n, a, m % a, b, ++cnt, (d - 1) * p + q, d * p + q);
  return cnt & 1 ? m - 1 - c : a - 1 - c;
}

}  // namespace tifa_libs::math

#endif