#ifndef TIFALIBS_MATH_KTH_ROOT
#define TIFALIBS_MATH_KTH_ROOT

#include "../math/isqrt.hpp"
#include "../math/qpow_mod.hpp"
#include "../nt/gcd.hpp"
#include "../nt/inverse.hpp"

namespace tifa_libs::math {

CEXP std::optional<u64> kth_root(u64 a, u64 k, u64 p) {
  if (k > 0 && !(a % p)) return 0;
  k %= p - 1;
  u64 g = gcd(k, p - 1);
  if (qpow_mod(a, (p - 1) / g, p) != 1) return {};
  a = qpow_mod(a, inverse(k / g, (p - 1) / g), p);
  auto pethr = [](u64 a, u64 p, u32 e, u64 m) {
    u64 q = m - 1;
    u32 s = 0;
    while (!(q % p)) q /= p, ++s;
    u64 pe = qpow_mod(p, e, m), ans = qpow_mod(a, (mul_mod_u(pe - 1, inverse(q, pe), pe) * q + 1) / pe, m), c = 2;
    while (qpow_mod(c, (m - 1) / p, m) == 1) ++c;
    c = qpow_mod(c, q, m);
    std::map<u64, u32> mp;
    u64 _a = 1;
    const u32 v = isqrt((s - e) * p) + 1;
    u64 _m = qpow_mod(c, mul_mod_u(v, qpow_mod(p, s - 1, m - 1), m - 1), m);
    for (u32 i = 0; i <= v; ++i, _a = mul_mod_u(_a, _m, m)) mp[_a] = i;
    _m = inverse(qpow_mod(c, qpow_mod(p, s - 1, m - 1), m), m);
    flt_ (u32, i, e, s) {
      u64 _ = mul_mod_u(a, inverse(qpow_mod(ans, pe, m), m), m), t = qpow_mod(_, qpow_mod(p, s - 1 - i, m - 1), m);
      fle_ (u32, j, 0, v) {
        if (mp.find(t) != mp.end()) {
          u32 x = mp[t];
          ans = mul_mod_u(ans, qpow_mod(c, mul_mod_u(j + v * x, qpow_mod(p, i - e, m - 1), m - 1), m), m);
          break;
        }
        t = mul_mod_u(t, _m, m);
        assert(j != v);
      }
    }
    return ans;
  };
  for (u64 d = 2; d * d <= g; ++d) {
    u32 n = 0;
    while (!(g % d)) g /= d, ++n;
    if (n) a = pethr(a, d, n, p);
  }
  if (g > 1) a = pethr(a, g, 1, p);
  return a;
}

}  // namespace tifa_libs::math

#endif