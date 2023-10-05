#ifndef TIFA_LIBS_MATH_QRESIDUE
#define TIFA_LIBS_MATH_QRESIDUE

#include "../bit/cntr0.hpp"
#include "inverse.hpp"
#include "qpow_mod.hpp"

namespace tifa_libs::math {

constexpr std::optional<i64> qresidue(u64 a, u64 p) {
  if (!(a %= p)) return 0;
  auto f = [](u64 a, u64 p) { return qpow_mod(a, p / 2, p) == 1; };
  if (!f(a, p)) return {};
  u64 r = 2;
  while (f(r, p)) ++r;
  int n = bit::cntr0(p - 1);
  u64 m = (p - 1) >> n, g = qpow_mod(r, m, p), e = 0, b = qpow_mod(a, m / 2, p), am = qpow_mod(a, m, p);
  for (int k = 1; k < n; ++k) e |= (u64)(qpow_mod(am * inverse(qpow_mod(g, e, p), p) % p, 1 << (n - 1 - k), p) == p - 1) << k;
  return (i64)(a * b % p * inverse(qpow_mod(g, e / 2, p), p) % p);
}

}  // namespace tifa_libs::math

#endif