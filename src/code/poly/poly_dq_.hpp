#ifndef TIFALIBS_POLY_DQ_
#define TIFALIBS_POLY_DQ_

#include "poly.hpp"

namespace tifa_libs::math {

template <class T, class Fodd, class Feven>
inline void poly_dq_(poly<T> &ans, size_t n, typename T::value_type v0, Fodd fodd, Feven feven) {
  if (n == 1) {
    ans[0] = v0;
    return;
  }
  if (n & 1) {
    poly_dq_(ans, n - 1, v0, fodd, feven);
    fodd(ans, n);
    return;
  }
  poly_dq_(ans, n / 2, v0, fodd, feven);
  feven(ans, n);
}

}  // namespace tifa_libs::math

#endif