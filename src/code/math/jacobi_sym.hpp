#ifndef TIFA_LIBS_MATH_JACOBI_SYMBOL
#define TIFA_LIBS_MATH_JACOBI_SYMBOL

#include "../bit/cntr0.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

constexpr int jacobi_sym(u64 a, u64 p) {
  assert(p & 1);
  if (!a) return 0;
  int s = 1, _ = 0;
  while (a > 1) {
    if (a == p || !a || p < 2) return 0;
    _ = bit::cntr0(a);
    if (((p - 1) & 7) && ((p + 1) & 7) && (_ & 1)) s = -s;
    if ((a >>= _) == 1) break;
    if ((((p - 1) & 7) * (a - 1)) & 7) s = -s;
    std::swap(a, p %= a);
  }
  return s;
}

}  // namespace tifa_libs::math

#endif