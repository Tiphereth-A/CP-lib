#ifndef TIFALIBS_MATH_JACOBI_SYM
#define TIFALIBS_MATH_JACOBI_SYM

#include "../util/alias_num.hpp"

namespace tifa_libs::math {

CEXP int jacobi_sym(u64 a, u64 p) NE {
  if (assert(p & 1); !a) return 0;
  int s = 1, _ = 0;
  while (a > 1) {
    if (a == p || !a || p < 2) return 0;
    if (_ = std::countr_zero(a); ((p - 1) & 7) && ((p + 1) & 7) && (_ & 1)) s = -s;
    if ((a >>= _) == 1) break;
    if ((((p - 1) & 7) * (a - 1)) & 7) s = -s;
    swap(a, p %= a);
  }
  return s;
}

}  // namespace tifa_libs::math

#endif