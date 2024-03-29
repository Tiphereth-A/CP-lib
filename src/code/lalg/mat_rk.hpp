#ifndef TIFALIBS_LALG_MAT_RK
#define TIFALIBS_LALG_MAT_RK

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class Ge>
constexpr u64 do_rank(Mat &mat, Ge &&ge) { return (u64)abs(ge(mat, false)); }
template <class Mat, class Ge>
constexpr u64 rank(Mat const &mat, Ge &&ge) {
  auto _ = mat;
  return do_rank(_, std::forward<Ge>(ge));
}

}  // namespace tifa_libs::math

#endif