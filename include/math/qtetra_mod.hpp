#ifndef TIFALIBS_MATH_QTETRA_MOD
#define TIFALIBS_MATH_QTETRA_MOD

#include "../nt/euler_phi.hpp"

namespace tifa_libs::math {
namespace qtetra_mod_impl_ {
CEXP u64 mpow(u64 a, u64 b, u64 m, u64& f) NE {
  retif_((a == 1 || b == 0) [[unlikely]], 1);
  u64 v = 1, x = a, z = m;
  f |= x >= z, x %= m;
  while (true) {
    if (b & 1) v *= x;
    if (v >= z) f = 1, v %= m;
    if (!(b >>= 1)) break;
    if ((x *= x) >= z) f = 1, x %= m;
  }
  return v;
}

CEXP u64 qtetra(u64 a, u64 b, u64 m, u64& f) NE {
  if (a == 0) return ~b & 1;
  if (m == 1) return f = 1;
  if (a == 1 || b == 0) return 1;
  if (b == 1) return a % m + (f |= (a >= m)) * m;
  u64 z = qtetra(a, b - 1, euler_phi(m), f), r = mpow(a, z, m, f);
  return r + f * m;
}
}  // namespace qtetra_mod_impl_

CEXP u64 qtetra_mod(u64 a, u64 b, u64 m) NE {
  u64 f = 0;
  return qtetra_mod_impl_::qtetra(a, b, m, f) % m;
}

}  // namespace tifa_libs::math

#endif