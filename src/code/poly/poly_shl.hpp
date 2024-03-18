#ifndef TIFALIBS_POLY_POLY_SHL
#define TIFALIBS_POLY_POLY_SHL

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr poly poly_shl(poly const &p, usz x) {
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