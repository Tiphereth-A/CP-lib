#ifndef TIFALIBS_POLY_POLY_SHR
#define TIFALIBS_POLY_POLY_SHR

#include "poly.hpp"

namespace tifa_libs::math {

template <class T>
constexpr poly<T> poly_shr(poly<T> const &p, usz x) {
  if (!x) return p;
  auto _ = p;
  if (x >= p.size()) {
    std::fill(_.data().begin(), _.data().end(), 0);
    return _;
  }
  std::fill(std::move(std::next(_.data().begin(), (isz)x), _.data().end(), _.data().begin()), _.data().end(), 0);
  return _;
}
template <class T>
constexpr poly<T> poly_shr_strip(poly<T> const &p, usz x) {
  auto _ = poly_shr(p, x);
  _.strip();
  return _;
}

}  // namespace tifa_libs::math

#endif