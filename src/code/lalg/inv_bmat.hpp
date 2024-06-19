#ifndef TIFALIBS_LALG_INV_BMAT
#define TIFALIBS_LALG_INV_BMAT

#include "ge_bmat.hpp"

namespace tifa_libs::math {

template <usz N>
CEXP std::optional<bitmat<N>> inv_bmat(bitmat<N> CR mat, u32 n) {
  bitmat<N, N * 2> _;
  flt_ (u32, i, 0, n) {
    for (auto p = mat[i]._Find_first(); p < n; p = mat[i]._Find_next(p)) _[i]._Unchecked_set(p);
    _[i]._Unchecked_set(i + n);
  }
  if (ge_bmat(_, true) != n) return {};
  flt_ (u32, i, 0, n)
    if (!_[i][i]) return {};
  bitmat<N> ret;
  flt_ (u32, i, 0, n)
    for (auto p = _[i]._Find_next(n - 1); p < n * 2; p = _[i]._Find_next(p)) ret[i]._Unchecked_set(p - n);
  return ret;
}

}  // namespace tifa_libs::math

#endif