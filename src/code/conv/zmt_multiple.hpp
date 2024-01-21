#ifndef TIFALIBS_CONV_ZMT_MULTIPLE
#define TIFALIBS_CONV_ZMT_MULTIPLE

#include "../nt/prime_seq.hpp"

namespace tifa_libs::math {

template <class T>
constexpr void zt_multiple(vec<T>& a, vec<u32> const& pf) {
  for (u32 p : pf)
    for (u64 k = (a.size() - 1) / p; k; --k) a[k] += a[k * p];
}
template <class T>
constexpr void zt_multiple(vec<T>& a) { zt_multiple(a, prime_seq(a.size() - 1)); }
template <class T>
constexpr void mt_multiple(vec<T>& a, vec<u32> const& pf) {
  for (u32 p : pf)
    for (u64 k = 1; k * p < a.size(); ++k) a[k] -= a[k * p];
}
template <class T>
constexpr void mt_multiple(vec<T>& a) { mt_multiple(a, prime_seq(a.size() - 1)); }

}  // namespace tifa_libs::math

#endif