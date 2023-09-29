#ifndef TIFA_LIBS_MATH_SPMAT_MERGE_LR
#define TIFA_LIBS_MATH_SPMAT_MERGE_LR

#include "../util/util.hpp"

#include "spmat.hpp"

namespace tifa_libs::math {

// [l] [r] -> [l r]
template <class T>
inline spmat<T> spmat_merge_lr(spmat<T> const &l, spmat<T> const &r) {
  size_t r_ = l.row(), lc_ = l.col();
  assert(r_ == r.row());
  spmat<T> ret(r_, lc_ + r.col());
  for (size_t i = 0; i < r_; ++i)
    if (!l.data()[i].empty()) ret.data()[i] = l.data()[i];
  for (size_t i = 0; i < r_; ++i)
    for (auto &&[j, v] : r.data()[i]) ret.data()[i].emplace_back(j + lc_, v);
  return ret;
}

}  // namespace tifa_libs::math

#endif