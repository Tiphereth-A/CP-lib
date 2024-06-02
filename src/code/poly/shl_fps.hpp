#ifndef TIFALIBS_POLY_SHL_FPS
#define TIFALIBS_POLY_SHL_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP poly<mint, ccore> shl_fps(poly<mint, ccore> CR p, usz x) {
  if (!x) return p;
  if (auto _ = p; x >= _.size()) return std::ranges::fill(_.data(), 0), _;
  else return std::fill(_.data().begin(), std::move_backward(_.data().begin(), std::prev(_.data().end(), (isz)x), _.data().end()), 0), _;
}

}  // namespace tifa_libs::math

#endif