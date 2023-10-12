#ifndef TIFA_LIBS_MATH_PARTITION_GEN
#define TIFA_LIBS_MATH_PARTITION_GEN

#include "../poly/poly.hpp"
#include "../poly/poly_inv.hpp"

namespace tifa_libs::math {

// partition[i] = p(i), i=0,1,...,n
template <class T>
inline poly<T> partition_gen(u64 n) {
  poly<T> a(n + 1);
  a[0] = 1;
  for (u64 k = 1; k <= n; ++k) {
    u64 k1 = k * (3 * k + 1) / 2;
    u64 k2 = k * (3 * k - 1) / 2;
    if (k2 > n) break;
    if (k1 <= n) a[k1] += ((k & 1) ? -1 : 1);
    if (k2 <= n) a[k2] += ((k & 1) ? -1 : 1);
  }
  return poly_inv(a);
}

}  // namespace tifa_libs::math

#endif