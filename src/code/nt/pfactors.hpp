#ifndef TIFALIBS_MATH_PFACTORS
#define TIFALIBS_MATH_PFACTORS

#include "../edh/discretization.hpp"
#include "../math/mul_mod.hpp"
#include "../rand/gen.hpp"
#include "gcd.hpp"
#include "is_prime.hpp"

namespace tifa_libs::math {
namespace pfactors_impl_ {
static rand::Gen<u64> e;
static auto __ = [] { e.seed(); return 0; }();
CEXP u64 rho(u64 n) NE {
  e.range(1, n - 1);
  auto f = [n, r = e()](u64 x) NE { return (mul_mod_u(x, x, n) + r) % n; };
  u64 g = 1, x = 0, y = e(), yy = 0;
  const u32 LIM = 128;
  for (u64 r = 1, q = 1; g == 1; r *= 2) {
    x = y;
    flt_ (u64, i, 0, r) y = f(y);
    for (u64 k = 0; g == 1 && k < r; k += LIM) {
      yy = y;
      for (u64 i = 0; i < LIM && i < r - k; ++i) q = mul_mod_u(q, (n - (y = f(y)) + x) % n, n);
      g = gcd(q, n);
    }
  }
  if (g == n) do {
      g = gcd((x + (n - (yy = f(yy)))) % n, n);
    } while (g == 1);
  return g == n ? rho(n) : g;
}
CEXP void run(u64 n, vecuu &p) NE {
  if (n < 2) return;
  if (is_prime(n)) return p.push_back(n);
  const u64 g = rho(n);
  run(n / g, p), run(g, p);
}
}  // namespace pfactors_impl_

template <bool unique = true>
CEXP vecuu pfactors(u64 n) NE {
  vecuu p;
  if (u32 _ = (u32)std::countr_zero(n) & 63; _) {
    n >>= _;
    if CEXP (unique) p.push_back(2);
    else p.assign(_, 2);
  }
  if (n < 2) return p;
  pfactors_impl_::run(n, p);
  if CEXP (unique) return uniq(p);
  std::ranges::sort(p);
  return p;
}
CEXP vecp<u64, u32> pf_exp(u64 n) NE {
  auto p = pfactors<false>(n);
  vecp<u64, u32> ans;
  for (u64 lst = 0; u64 i : p)
    if (i != lst) ans.emplace_back(lst = i, 1);
    else ++ans.back().second;
  return ans;
}

}  // namespace tifa_libs::math

#endif