#ifndef TIFA_LIBS_MATH_EXGCD
#define TIFA_LIBS_MATH_EXGCD

#include "../util/util.hpp"

namespace tifa_libs::math {

// @return tuple(g, x, y) s.t. g = gcd(a, b), xa + yb = g, |x| + |y| is the minimal (primary) and x <= y (secondarily)
constexpr std::tuple<u64, i64, i64> exgcd(i64 a, i64 b) {
  i64 x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b) {
    i64 c = a / b;
    std::tie(x1, x2, x3, x4, a, b) = std::make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
  }
  return {a, x1, x2};
}

}  // namespace tifa_libs::math

#endif