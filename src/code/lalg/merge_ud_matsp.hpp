#ifndef TIFALIBS_LALG_MERGE_UD_MATSP
#define TIFALIBS_LALG_MERGE_UD_MATSP

#include "matsp.hpp"

namespace tifa_libs::math {

// [u] [d] -> [u; d]
template <class T>
constexpr matsp<T> merge_ud_matsp(matsp<T> const &u, matsp<T> const &d) {
  u32 ur_ = u.row(), dr_ = d.row(), c_ = u.col();
  assert(c_ == d.col());
  matsp<T> ret(ur_ + dr_, c_);
  for (u32 i = 0; i < ur_; ++i)
    if (!u.data()[i].empty()) ret.data()[i] = u.data()[i];
  for (u32 i = 0; i < dr_; ++i)
    if (!d.data()[i].empty()) ret.data()[i + ur_] = d.data()[i];
  return ret;
}

}  // namespace tifa_libs::math

#endif