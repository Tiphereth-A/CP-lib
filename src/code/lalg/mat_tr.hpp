#ifndef TIFALIBS_LALG_MAT_TR
#define TIFALIBS_LALG_MAT_TR

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat>
constexpr auto trace(Mat const &mat) {
  u32 n = mat.row();
  assert(n == mat.col());
  typename Mat::value_type ret{};
  for (u32 i = 0; i < n; ++i) ret += mat(i, i);
  return ret;
}

}  // namespace tifa_libs::math

#endif