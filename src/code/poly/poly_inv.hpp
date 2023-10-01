#ifndef TIFALIBS_POLY_INV
#define TIFALIBS_POLY_INV

#include "poly.hpp"

namespace tifa_libs::math {

namespace polyinv_detail_ {
template <class T>
constexpr void inv_(poly<T> const &p, poly<T> &ans, size_t n) {
  using mint = typename T::value_type;
  if (n == 1) {
    ans[0] = p[0].inv();
    return;
  }
  if (n & 1) {
    inv_(p, ans, n - 1);
    --n;
    mint _ = 0;
    for (size_t i = 0; i < n; ++i) _ += ans[i] * p[n - i];
    ans.data().push_back(_ * (-p[0]).inv());
    return;
  }
  inv_(p, ans, n / 2);
  auto sA = p;
  sA.conv(ans);
  sA.conv(ans);
  sA.resize(n);
  ans = ans * 2 - sA;
}
}  // namespace polyinv_detail_

template <class T>
inline poly<T> poly_inv(poly<T> const &p) {
  poly<T> ans;
  polyinv_detail_::inv_(p, ans, p.size());
  return ans;
}

}  // namespace tifa_libs::math

#endif