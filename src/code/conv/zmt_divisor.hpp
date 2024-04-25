#ifndef TIFALIBS_CONV_ZMT_DIVISOR
#define TIFALIBS_CONV_ZMT_DIVISOR

#include "../nt/prime_seq.hpp"

namespace tifa_libs::math {

template <class T>
CEXP void zt_divisor(vec<T>& a, vecu CR pf) {
  for (u32 p : pf)
    for (u64 k = 1; k * p < a.size(); ++k) a[k * p] += a[k];
}
template <class T>
CEXP void zt_divisor(vec<T>& a) { zt_divisor(a, prime_seq(a.size() - 1)); }
template <class T>
CEXP void mt_divisor(vec<T>& a, vecu CR pf) {
  for (u32 p : pf)
    for (u64 k = (a.size() - 1) / p; k; --k) a[k * p] -= a[k];
}
template <class T>
CEXP void mt_divisor(vec<T>& a) { mt_divisor(a, prime_seq(a.size() - 1)); }

}  // namespace tifa_libs::math

#endif