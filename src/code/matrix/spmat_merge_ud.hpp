#ifndef TIFA_LIBS_MATH_SPMAT_MERGE_UD
#define TIFA_LIBS_MATH_SPMAT_MERGE_UD

#include "spmat.hpp"

namespace tifa_libs::math {

// [u] [d] -> [u; d]
template <class T>
inline spmat<T> spmat_merge_ud(const spmat<T> &u, const spmat<T> &d) {
  size_t ur_ = u.row(), dr_ = d.row(), c_ = u.col();
  assert(c_ == d.col());
  spmat<T> ret(ur_ + dr_, c_);
  for (size_t i = 0; i < ur_; ++i)
    if (!u.data()[i].empty()) ret.data()[i] = u.data()[i];
  for (size_t i = 0; i < dr_; ++i)
    if (!d.data()[i].empty()) ret.data()[i + ur_] = d.data()[i];
  return ret;
}

}  // namespace tifa_libs::math

#endif