#ifndef TIFA_LIBS_MATH_KTH_ROOT
#define TIFA_LIBS_MATH_KTH_ROOT

#include "../math/inverse.hpp"
#include "../math/isqrt.hpp"
#include "../math/qpow_mod.hpp"

namespace tifa_libs::math {

inline std::optional<u64> kth_root(u64 a, u64 k, u64 p) {
  if (k > 0 && !(a % p)) return 0;
  k %= p - 1;
  u64 g = std::gcd(k, p - 1);
  if (qpow_mod(a, (p - 1) / g, p) != 1) return {};
  a = qpow_mod(a, inverse(k / g, (p - 1) / g), p);
  auto peth_root = [](u64 a, u64 p, u32 e, u64 mod) {
    u64 q = mod - 1;
    u32 s = 0;
    while (q % p == 0) {
      q /= p;
      ++s;
    }
    u64 pe = qpow_mod(p, e, mod), ans = qpow_mod(a, ((pe - 1) * inverse(q, pe) % pe * q + 1) / pe, mod), c = 2;
    while (qpow_mod(c, (mod - 1) / p, mod) == 1) ++c;
    c = qpow_mod(c, q, mod);
    std::map<u64, u32> map;
    u64 add = 1;
    u32 v = isqrt((s - e) * p) + 1;
    u64 mul = qpow_mod(c, v * qpow_mod(p, s - 1, mod - 1) % (mod - 1), mod);
    for (u32 i = 0; i <= v; ++i) {
      map[add] = i;
      add = add * mul % mod;
    }
    mul = inverse(qpow_mod(c, qpow_mod(p, s - 1, mod - 1), mod), mod);
    for (u32 i = e; i < s; ++i) {
      u64 err = inverse(qpow_mod(ans, pe, mod), mod) * a % mod, target = qpow_mod(err, qpow_mod(p, s - 1 - i, mod - 1), mod);
      for (u32 j = 0; j <= v; ++j) {
        if (map.find(target) != map.end()) {
          u32 x = map[target];
          ans = ans * qpow_mod(c, (j + v * x) * qpow_mod(p, i - e, mod - 1) % (mod - 1), mod) % mod;
          break;
        }
        target = target * mul % mod;
        assert(j != v);
      }
    }
    return ans;
  };
  for (u64 div = 2; div * div <= g; ++div) {
    u32 sz = 0;
    while (!(g % div)) {
      g /= div;
      ++sz;
    }
    if (sz) a = peth_root(a, div, sz, p);
  }
  if (g > 1) a = peth_root(a, g, 1, p);
  return a;
}

}  // namespace tifa_libs::math

#endif