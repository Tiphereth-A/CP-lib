#ifndef TIFALIBS_POLY_INV
#define TIFALIBS_POLY_INV

#include "poly_dq_.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_inv(poly<T> const &p) {
  using mint = typename T::value_type;
  poly<T> ans;
  poly_dq_(
    ans,
    p.size(),
    p[0].inv(),
    [&p](poly<T> &ans, size_t n) {
      --n;
      mint _ = 0;
      for (size_t i = 0; i < n; ++i) _ += ans[i] * p[n - i];
      ans.data().push_back(_ * (-p[0]).inv());
    },
    [&p](poly<T> &ans, size_t n) {
      auto sA = p;
      sA.resize(n);
      sA.conv(ans, n);
      sA.conv(ans, n);
      ans = ans * 2 - sA;
    });
  return ans;
}

}  // namespace tifa_libs::math

#endif