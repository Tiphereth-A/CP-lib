#ifndef TIFALIBS_LALG_MERGE_LR_MATSP
#define TIFALIBS_LALG_MERGE_LR_MATSP

#include "matsp.hpp"

namespace tifa_libs::math {

// [l] [r] -> [l r]
template <class T>
CEXP matsp<T> merge_lr_matsp(cT_(matsp<T>) l, cT_(matsp<T>) r) NE {
  const u32 r_ = l.row(), lc_ = l.col();
  assert(r_ == r.row());
  matsp<T> ret(r_, lc_ + r.col());
  flt_ (u32, i, 0, r_)
    if (!l.data()[i].empty()) ret.data()[i] = l.data()[i];
  flt_ (u32, i, 0, r_)
    for (auto &&[j, v] : r.data()[i]) ret.data()[i].emplace_back(j + lc_, v);
  return ret;
}

}  // namespace tifa_libs::math

#endif