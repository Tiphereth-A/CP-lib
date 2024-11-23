#ifndef TIFALIBS_MATH_SQRFREE_CNT
#define TIFALIBS_MATH_SQRFREE_CNT

#include "../math/ikth_root.hpp"
#include "../math/isqrt.hpp"
#include "lsieve.hpp"
#include "lsieve_func.hpp"

namespace tifa_libs::math {

CEXP u64 sqrfree_cnt(u64 n, veci mu) {
  if (n <= 3) return n;
  const u32 I = (u32)min(ikth_root(n, 5) * 2, ikth_root(n / 4, 3)), D = isqrt(n / I);
  u64 ans = 0;
  flt_ (u32, i, 1, D + 1)
    if (mu[i]) ans += (u64)mu[i] * (n / ((u64)i * i));
  flt_ (u32, i, 1, D + 1) mu[i] += mu[i - 1];
  veci mu_large(I + 1);
  for (u32 i = I - 1; i >= 1; --i) {
    const u32 xi = isqrt(n / i), h = isqrt(xi), tlim = 2 * h - (h == xi / h);
    auto f = [xi, h, tlim](u32 i) -> u32 { return i < h ? i + 1 : u32(f64(xi) / (2 * h - (tlim & 1) - i)); };
    i64 sum = 1;
    for (u32 t = 1, l = 1; t < tlim; ++t) {
      const u32 r = f(t), q = f(tlim - t - 1);
      sum -= i64(r - l) * (q <= D ? mu[q] : mu_large[(u64)i * r * r]), l = r;
    }
    ans += u64(mu_large[i] = (i32)sum);
  }
  return ans - u64(i64(I - 1) * mu[D]);
}
CEXP u64 sqrfree_cnt(u64 n) {
  if (n <= 3) return n;
  const u32 I = (u32)min(ikth_root(n, 5) * 2, ikth_root(n / 4, 3)), D = isqrt(n / I);
  return sqrfree_cnt(n, lsieve<ls_mu>(D + 1).mu);
}

}  // namespace tifa_libs::math

#endif