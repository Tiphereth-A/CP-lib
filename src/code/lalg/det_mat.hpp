#ifndef TIFALIBS_LALG_DET_MAT
#define TIFALIBS_LALG_DET_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class Ge>
requires requires(Ge ge, Mat A, bool clear_u) {
  { ge(A, clear_u) } -> std::same_as<i32>;
}
CEXP auto det(Mat mat, Ge&& ge) NE {
  using T = TPN Mat::val_t;
  const u32 n = mat.row();
  assert(n == mat.col());
  const i64 rk_ = ge(mat, false);
  if CEXP (std::is_same_v<T, bool>) return abs(rk_) == n;
  else {
    if ((u32)abs(rk_) != n) return T{};
    T ret = mat(0, 0);
    flt_ (u32, i, 1, n) ret *= mat(i, i);
    return T(rk_ < 0 ? -ret : ret);
  }
}

}  // namespace tifa_libs::math

#endif