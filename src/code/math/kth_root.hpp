#ifndef TIFA_LIBS_MATH_KTH_ROOT
#define TIFA_LIBS_MATH_KTH_ROOT

#include "../math/bsgs.hpp"
#include "../math/inverse.hpp"
#include "../math/pfactors.hpp"
#include "../math/qpow_mod.hpp"

namespace tifa_libs::math {

inline std::optional<u64> kth_root(u64 a, u64 k, u64 p) {
  if (!k) {
    if (a != 1) return {};
    return a;
  }
  if (a <= 1 || k <= 1 || p == 2) return a;
  a %= p;
  u64 g = std::gcd(k, p - 1);
  if (qpow_mod(a, (p - 1) / g, p) != 1) return {};
  auto pps = pfactors(g);
  u64 k2 = inverse(k / g, (p - 1) / g);
  rand::Gen<std::uniform_int_distribution<u64>> rnd(2, p - 1);
  u64 c = qpow_mod(a, k2, p);
  for (auto [q, e] : pps) {
    u64 s = p - 1, t = 0;
    while (!(s % q)) {
      s /= q;
      ++t;
    }
    u64 v;
    while (1)
      if (qpow_mod(v = rnd(), (p - 1) / q, p) != 1) break;
    u64 qe = qpow_mod(q, e, p), u = qe - inverse(s, qe), z = qpow_mod(c, (s * u + 1) / qe, p), qi = qpow_mod(q, t - 1 - e, p);
    for (u64 i = t - 1 - e; ~i; --i) {
      u64 z2 = qpow_mod(v, s * qpow_mod(q, t - 1 - e - i, p), p);
      auto L = bsgs(qpow_mod(z2, qe * qi, p), c * qpow_mod(qpow_mod(z, (p - 2) * qe, p), qi, p), q);
      if (!L.has_value()) return {};
      z *= qpow_mod(z2, L.value(), p);
      qi /= q;
    }
    c = z;
  }
  return c;
}

}  // namespace tifa_libs::math

#endif