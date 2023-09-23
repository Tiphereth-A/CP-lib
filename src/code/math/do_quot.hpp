#ifndef TIFA_LIBS_MATH_DO_QUOT
#define TIFA_LIBS_MATH_DO_QUOT

#include "../util/util.hpp"

namespace tifa_libs::math {

inline void do_quot(u64 n, std::function<void(u64, u64, u64)> f) {
  for (u64 l = 1, r = 0, ed_ = n; l <= ed_; l = r + 1) f(l, r = n / (n / l), n / l);
}

}  // namespace tifa_libs::math

#endif