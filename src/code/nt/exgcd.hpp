#ifndef TIFALIBS_MATH_EXGCD
#define TIFALIBS_MATH_EXGCD

#include "../util/traits.hpp"

namespace tifa_libs::math {

// @return tuple(g, x, y) s.t. g = gcd(a, b), xa + yb = g, |x| + |y| is the minimal (primary) and x <= y (secondarily)
template <sint_c T, class U = to_uint_t<T>>
constexpr std::tuple<U, T, T> exgcd(T a, T b) {
  T x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b) {
    T c = a / b;
    std::tie(x1, x2, x3, x4, a, b) = std::make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
  }
  return {a, x1, x2};
}

}  // namespace tifa_libs::math

#endif