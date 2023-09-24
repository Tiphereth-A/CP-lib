#ifndef TIFA_LIBS_MATH_MAT_MERGE_LR
#define TIFA_LIBS_MATH_MAT_MERGE_LR

#include "../util/util.hpp"

#include "mat.hpp"

namespace tifa_libs::math {

// [l] [r] -> [l r]
template <class T>
inline matrix<T> merge_lr(matrix<T> const &l, matrix<T> const &r) {
  assert(l.row_size() == r.row_size());
  matrix<T> ret(l.row_size(), l.col_size() + r.col_size());
  ret.data()[std::gslice(0, {l.row_size(), l.col_size()}, {ret.col_size(), 1})] = l.data();
  ret.data()[std::gslice(l.col_size(), {r.row_size(), r.col_size()}, {ret.col_size(), 1})] = r.data();
  return ret;
}

}  // namespace tifa_libs::math

#endif