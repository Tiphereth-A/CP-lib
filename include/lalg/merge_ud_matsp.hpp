#ifndef TIFALIBS_LALG_MERGE_UD_MATSP
#define TIFALIBS_LALG_MERGE_UD_MATSP

#include "matsp.hpp"

namespace tifa_libs::math {

// [u] [d] -> [u; d]
template <class T>
CEXP matsp<T> merge_ud_matsp(cT_(matsp<T>) u, cT_(matsp<T>) d) NE {
  const u32 ur_ = u.row(), dr_ = d.row(), c_ = u.col();
  assert(c_ == d.col());
  matsp<T> ret(ur_ + dr_, c_);
  flt_ (u32, i, 0, ur_)
    if (!u.data()[i].empty()) ret.data()[i] = u.data()[i];
  flt_ (u32, i, 0, dr_)
    if (!d.data()[i].empty()) ret.data()[i + ur_] = d.data()[i];
  return ret;
}

}  // namespace tifa_libs::math

#endif