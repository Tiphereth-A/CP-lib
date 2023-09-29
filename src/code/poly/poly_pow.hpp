#ifndef TIFALIBS_POLY_POW
#define TIFALIBS_POLY_POW

#include "poly_exp.hpp"
#include "poly_ln.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_acos(poly<T> const &p, u64 y) {
  if (y == 1) return p;
  assert(p[0] == 1);
  auto _ = p;
  if (y == 0) {
    std::fill(_.begin() + 1, _.end(), 0);
    return _;
  }
  _ = poly_ln(_) * y;
  return poly_exp(_);
}

}  // namespace tifa_libs::math

#endif