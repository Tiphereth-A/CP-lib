#ifndef TIFALIBS_MATH_QRESIDUE
#define TIFALIBS_MATH_QRESIDUE

#include "../math/qpow_mod.hpp"
#include "inverse.hpp"

namespace tifa_libs::math {

CEXP auto qresidue(u64 a, u64 p) NE {
  std::optional<u64> ret;
  if (!(a %= p)) {
    ret.emplace(0);
    return ret;
  }
  auto f = [](u64 a, u64 p) NE { return qpow_mod(a, p / 2, p) == 1; };
  if (!f(a, p)) return ret;
  u64 r = 2;
  while (f(r, p)) ++r;
  const int n = std::countr_zero(p - 1);
  const u64 m = (p - 1) >> n, g = qpow_mod(r, m, p), b = qpow_mod(a, m / 2, p), am = qpow_mod(a, m, p);
  u64 e = 0;
  flt_ (int, k, 1, n) e |= (u64)(qpow_mod(am * inverse(qpow_mod(g, e, p), p) % p, 1 << (n - 1 - k), p) == p - 1) << k;
  ret.emplace(a * b % p * inverse(qpow_mod(g, e / 2, p), p) % p);
  return ret;
}

}  // namespace tifa_libs::math

#endif