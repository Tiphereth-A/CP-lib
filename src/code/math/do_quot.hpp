#ifndef TIFALIBS_MATH_DO_QUOT
#define TIFALIBS_MATH_DO_QUOT

#include "div64.hpp"

namespace tifa_libs::math {

template <class F>
requires requires(F f, u64 n) {
  { f(n, n, n) };
}
constexpr void do_quot(u64 n, F f, u64 l_begin = 1) {
  for (u64 l = l_begin, r = 0, ed_ = n; l <= ed_; l = r + 1) f(l, r = div_u64(n, div_u64(n, l)), div_u64(n, l));
}

}  // namespace tifa_libs::math

#endif