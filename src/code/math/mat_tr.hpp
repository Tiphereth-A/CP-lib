#ifndef TIFA_LIBS_MATH_MAT_TR
#define TIFA_LIBS_MATH_MAT_TR

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class T = typename Mat::value_type>
inline T trace(Mat const &mat) {
  size_t n = mat.row();
  assert(n == mat.col());
  T ret{};
  for (size_t i = 0; i < n; ++i) ret += mat(i, i);
  return ret;
}

}  // namespace tifa_libs::math

#endif