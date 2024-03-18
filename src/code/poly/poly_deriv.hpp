#ifndef TIFALIBS_POLY_POLY_DERIV
#define TIFALIBS_POLY_POLY_DERIV

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr poly poly_deriv(poly const &p) {
  auto _ = p;
  for (u32 i = 1; i < _.size(); ++i) _[i - 1] = _[i] * i;
  _.data().back() = 0;
  return _;
}

}  // namespace tifa_libs::math

#endif