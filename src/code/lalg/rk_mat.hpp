#ifndef TIFALIBS_LALG_RK_MAT
#define TIFALIBS_LALG_RK_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class Ge>
requires requires(Ge ge, Mat A, bool clear_u) {
  { ge(A, clear_u) } -> std::same_as<i32>;
}
CEXP u32 do_rank(Mat &mat, Ge &&ge) { return (u32)abs(ge(mat, false)); }
template <class Mat, class Ge>
CEXP u32 rank(Mat CR mat, Ge &&ge) {
  auto _ = mat;
  return do_rank(_, std::forward<Ge>(ge));
}

}  // namespace tifa_libs::math

#endif