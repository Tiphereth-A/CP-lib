#ifndef TIFALIBS_LALG_MERGE_LR_MATSP
#define TIFALIBS_LALG_MERGE_LR_MATSP

#include "matsp.hpp"

namespace tifa_libs::math {

// [l] [r] -> [l r]
template <class T>
constexpr matsp<T> merge_lr_matsp(matsp<T> const &l, matsp<T> const &r) {
  u32 r_ = l.row(), lc_ = l.col();
  assert(r_ == r.row());
  matsp<T> ret(r_, lc_ + r.col());
  for (u32 i = 0; i < r_; ++i)
    if (!l.data()[i].empty()) ret.data()[i] = l.data()[i];
  for (u32 i = 0; i < r_; ++i)
    for (auto &&[j, v] : r.data()[i]) ret.data()[i].emplace_back(j + lc_, v);
  return ret;
}

}  // namespace tifa_libs::math

#endif