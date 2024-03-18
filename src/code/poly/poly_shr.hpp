#ifndef TIFALIBS_POLY_POLY_SHR
#define TIFALIBS_POLY_POLY_SHR

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr poly poly_shr(poly const &p, usz x) {
  if (!x) return p;
  auto _ = p;
  if (x >= p.size()) {
    std::fill(_.data().begin(), _.data().end(), 0);
    return _;
  }
  std::fill(std::move(_.data().begin() + (isz)x, _.data().end(), _.data().begin()), _.data().end(), 0);
  return _;
}
template <class poly>
constexpr poly poly_shr_strip(poly const &p, usz x) {
  auto _ = poly_shr(p, x);
  _.strip();
  return _;
}

}  // namespace tifa_libs::math

#endif