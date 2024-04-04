#ifndef TIFALIBS_LALG_MUL_BMAT
#define TIFALIBS_LALG_MUL_BMAT

#include "bitmat.hpp"

namespace tifa_libs::math {

template <usz I, usz J, usz K>
constexpr bitmat<I, K> mul_bmat(bitmat<I, J> const &l, bitmat<K, J> const &trans_r) {
  bitmat<I, K> ret;
  for (usz i = 0; i < I; ++i)
    for (u32 k = 0; k < K; ++k) ret[i][k] = (l[i] & trans_r[k]).count() & 1;
  return ret;
}

}  // namespace tifa_libs::math

#endif