#ifndef TIFALIBS_LALG_MAT_DET
#define TIFALIBS_LALG_MAT_DET

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class Ge>
constexpr auto det(Mat mat, Ge ge) {
  using T = typename Mat::value_type;
  u32 n = mat.row();
  assert(n == mat.col());
  i64 rk_ = ge(mat, false);
  if constexpr (std::is_same_v<T, bool>) return abs(rk_) == n;
  else {
    if ((u32)abs(rk_) != n) return T{};
    T ret = mat(0, 0);
    for (u32 i = 1; i < n; ++i) ret *= mat(i, i);
    return T(rk_ < 0 ? -ret : ret);
  }
}

}  // namespace tifa_libs::math

#endif