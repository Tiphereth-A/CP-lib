#ifndef TIFALIBS_POLY_EXP
#define TIFALIBS_POLY_EXP

#include "poly_dq_.hpp"

namespace tifa_libs::math {

template <class T>
inline poly<T> poly_exp(poly<T> const &p) {
  using mint = typename T::value_type;
  assert(p[0] == 0);
  poly<T> ans;
  poly_dq_(
    ans,
    p.size(),
    1,
    [&p](poly<T> &ans, size_t n) -> void {
      n -= 2;
      mint _ = 0;
      for (size_t i = 0; i <= n; ++i) _ += (i + 1) * p[i + 1] * ans[n - i];
      ans.p.data().push_back(_ * mint(n + 1).inv());
    },
    [&p](poly<T> &ans, size_t n) -> void {
      auto ans_ln = ans;
      ans_ln.resize(n);
      ans_ln = poly_ln(ans_ln);
      for (size_t i = 0; i < ans_ln.size(); ++i) ans_ln[i] = p[i] - ans_ln[i];
      ++ans_ln[0];
      ans.conv(ans_ln, n);
    });
  return ans;
}

}  // namespace tifa_libs::math

#endif