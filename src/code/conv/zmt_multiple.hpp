#ifndef TIFALIBS_CONV_ZMT_MULTIPLE
#define TIFALIBS_CONV_ZMT_MULTIPLE

#include "../nt/prime_seq.hpp"

namespace tifa_libs::math {

template <class T>
CEXP void zt_multiple(vec<T>& a, spnu pf) NE {
  for (u32 p : pf)
    for (u64 k = (a.size() - 1) / p; k; --k) a[k] += a[k * p];
}
template <class T>
CEXP void zt_multiple(vec<T>& a) NE { zt_multiple(a, prime_seq(a.size() - 1)); }
template <class T>
CEXP void mt_multiple(vec<T>& a, spnu pf) NE {
  for (u32 p : pf)
    for (u64 k = 1; k * p < a.size(); ++k) a[k] -= a[k * p];
}
template <class T>
CEXP void mt_multiple(vec<T>& a) NE { mt_multiple(a, prime_seq(a.size() - 1)); }

}  // namespace tifa_libs::math

#endif