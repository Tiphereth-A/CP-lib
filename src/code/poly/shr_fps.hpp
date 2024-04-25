#ifndef TIFALIBS_POLY_SHR_FPS
#define TIFALIBS_POLY_SHR_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> shr_fps(poly<mint, ccore> CR p, usz x) {
  if (!x) return p;
  auto _ = p;
  if (x >= p.size()) {
    std::ranges::fill(_.data(), 0);
    return _;
  }
  std::fill(std::move(_.data().begin() + (isz)x, _.data().end(), _.data().begin()), _.data().end(), 0);
  return _;
}
template <class mint, class ccore>
CEXP poly<mint, ccore> shr_strip_fps(poly<mint, ccore> CR p, usz x) {
  auto _ = shr_fps(p, x);
  _.strip();
  return _;
}

}  // namespace tifa_libs::math

#endif