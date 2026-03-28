#pragma once

#include "../../ds/bmat/lib.hpp"

namespace tifa_libs {

template <usz I, usz J, usz K>
CEXP bitmat<I, K> mul_bmat(bitmat<I, J> CR l, bitmat<K, J> CR trans_r) NE {
  bitmat<I, K> ret;
  flt_ (usz, i, 0, I)
    flt_ (u32, k, 0, K) ret[i]._Unchecked_set(k, (l[i] & trans_r[k]).count() & 1);
  return ret;
}

}  // namespace tifa_libs
