#ifndef TIFALIBS_MATH_PI_MIN25
#define TIFALIBS_MATH_PI_MIN25

#include "../math/div64.hpp"
#include "../math/isqrt.hpp"
#include "../util/alias_others.hpp"

namespace tifa_libs::math {

CEXP u64 pi_min25(u64 n) NE {
  if (n <= 1) return 0;
  if (n == 2) return 1;
  const u32 lim = isqrt(n);
  u32 vn = (lim + 1) / 2;
  vecu s(vn), r(vn);
  flt_ (u32, cx, 0, vn) s[cx] = cx;
  flt_ (u32, cx, 0, vn) r[cx] = cx * 2 + 1;
  vecuu l(vn);
  flt_ (u32, cx, 0, vn) l[cx] = (n / (cx * 2 + 1) - 1) / 2;
  vecb vis(lim + 1);
  u32 cnt_p = 0;
  for (u32 p = 3; p <= lim; p += 2) {
    if (vis[p]) continue;
    u32 p2 = p * p;
    if ((u64)p2 * p2 > n) break;
    vis[p] = true;
    for (u32 cx = p2; cx <= lim; cx += p * 2) vis[cx] = true;
    u32 ns = 0;
    flt_ (u32, cx, 0, vn) {
      u32 cur = r[cx];
      if (vis[cur]) continue;
      u64 d = (u64)cur * p;
      l[ns] = l[cx] - (d <= lim ? l[s[d / 2] - cnt_p] : s[(div_u64d(n, d) - 1) / 2]) + cnt_p, r[ns++] = cur;
    }
    vn = ns;
    for (u32 cx = (lim - 1) / 2, cy = ((lim / p) - 1) | 1; cy >= p; cy -= 2)
      for (u32 cur = s[cy / 2] - cnt_p, cz = cy * p / 2; cz <= cx; --cx) s[cx] -= cur;
    ++cnt_p;
  }
  l[0] += u64(vn + (cnt_p - 1) * 2) * (vn - 1) / 2;
  flt_ (u32, cx, 1, vn) l[0] -= l[cx];
  flt_ (u32, cx, 1, vn) {
    u32 q = r[cx];
    u64 m = n / q;
    u32 e = s[(m / q - 1) / 2] - cnt_p;
    if (e < cx + 1) break;
    u64 t = 0;
    flt_ (u32, cy, cx + 1, e + 1) t += s[(div_u64d(m, r[cy]) - 1) / 2];
    l[0] += t - u64(e - cx) * (cnt_p + cx - 1);
  }
  return l[0] + 1;
}

}  // namespace tifa_libs::math

#endif