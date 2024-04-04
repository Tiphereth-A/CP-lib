#ifndef TIFALIBS_POLY_SHL_FPS
#define TIFALIBS_POLY_SHL_FPS

#include "poly.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
constexpr poly<mint, ccore> shl_fps(poly<mint, ccore> const &p, usz x) {
  if (!x) return p;
  auto _ = p;
  if (x >= _.size()) {
    std::fill(_.data().begin(), _.data().end(), 0);
    return _;
  }
  std::fill(_.data().begin(), std::move_backward(_.data().begin(), std::prev(_.data().end(), (isz)x), _.data().end()), 0);
  return _;
}

}  // namespace tifa_libs::math

#endif