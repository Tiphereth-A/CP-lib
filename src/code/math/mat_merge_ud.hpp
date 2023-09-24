#ifndef TIFA_LIBS_MATH_MAT_MERGE_UD
#define TIFA_LIBS_MATH_MAT_MERGE_UD

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

// [u] [d] -> [u; d]
template <class T>
inline matrix<T> merge_ud(const matrix<T> &u, const matrix<T> &d) {
  assert(u.col_size() == d.col_size());
  matrix<T> ret(u.row_size() + d.row_size(), u.col_size());
  ret.data()[std::slice(0, u.row_size() * u.col_size(), 1)] = u.data();
  ret.data()[std::slice(u.row_size() * u.col_size(), d.row_size() * d.col_size(), 1)] = d.data();
  return ret;
}

}  // namespace tifa_libs::math

#endif