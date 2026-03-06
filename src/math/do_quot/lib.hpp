#pragma once

#include "../div64/lib.hpp"

namespace tifa_libs::math {

template <class F>
requires requires(F f, u64 n) { f(n, n, n); }
CEXP void do_quot(u64 n, F f, u64 l_begin = 1) NE {
  for (u64 l = l_begin, r = 0, ed_ = n; l <= ed_; l = r + 1) f(l, r = div_u64(n, div_u64(n, l)), div_u64(n, l));
}

}  // namespace tifa_libs::math
