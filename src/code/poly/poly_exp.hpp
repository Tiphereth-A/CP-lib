#ifndef TIFALIBS_POLY_EXP
#define TIFALIBS_POLY_EXP

#include "poly_ln.hpp"

namespace tifa_libs::math {

namespace polyexp_detail_ {
template <class T>
constexpr void exp_(poly<T> const &p, poly<T> &ans, size_t n) {
  using mint = typename T::value_type;
  if (n == 1) {
    ans[0] = 1;
    return;
  }
  if (n & 1) {
    exp_(p, ans, n - 1);
    n -= 2;
    mint _ = 0;
    for (size_t i = 0; i <= n; ++i) _ += (i + 1) * p[i + 1] * ans[n - i];
    ans.data().push_back(_ * mint(n + 1).inv());
    return;
  }
  exp_(p, ans, n / 2);
  auto ans_ln = ans;
  ans_ln.resize(n);
  ans_ln = poly_ln(ans_ln);
  for (size_t i = 0; i < ans_ln.size(); ++i) ans_ln[i] = p[i] - ans_ln[i];
  ans_ln[0] = ans_ln[0] + 1;
  ans.conv(ans_ln);
  ans.resize(n);
}
}  // namespace polyexp_detail_

template <class T>
inline poly<T> poly_exp(poly<T> const &p) {
  assert(p[0] == 0);
  poly<T> ans;
  polyexp_detail_::exp_(p, ans, p.size());
  return ans;
}

}  // namespace tifa_libs::math

#endif