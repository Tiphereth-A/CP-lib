#ifndef TIFALIBS_POLY_CZT
#define TIFALIBS_POLY_CZT

#include "poly.hpp"

namespace tifa_libs::math {

// @brief Chirp Z-Transform
// @return {f(a*c^0), f(a*c^1), ..., f(a*c^{m-1})}
template <class T, class mint = typename T::value_type>
inline poly<T> poly_czt(poly<T> f, mint c, mint a = 1, u64 m = (u64)-1) {
  if (m == (u64)-1) m = f.size();
  if (f.data().empty() || !m) return poly<T>{};
  usz n = f.size();
  if (a != 1) {
    mint x = 1;
    for (u64 i = 0; i < n; ++i) f[i] *= x, x *= a;
  }
  if (c == 0) {
    poly<T> ans(m, f[0]);
    for (u64 i = 1; i < n; ++i) ans[0] += f[i];
    return ans;
  }
  poly<T> wc(m + n), iwc(std::max(m, n));
  mint ws = 1, iW = c.inv(), iws = 1;
  wc[0] = iwc[0] = 1;
  for (u64 i = 1; i < m + n; ++i) wc[i] = ws * wc[i - 1], ws *= c;
  for (u64 i = 1; i < std::max(m, n); ++i) iwc[i] = iws * iwc[i - 1], iws *= iW;
  for (u64 i = 0; i < n; ++i) f[i] *= iwc[i];
  std::reverse(f.data().begin(), f.data().end());
  poly<T> g = f * wc, ans(std::next(g.data().begin(), (isz)n - 1), std::next(g.data().begin(), isz(n + m) - 1));
  for (u64 i = 0; i < m; ++i) ans[i] *= iwc[i];
  return ans;
}

}  // namespace tifa_libs::math

#endif