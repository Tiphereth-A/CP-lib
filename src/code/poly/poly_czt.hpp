#ifndef TIFALIBS_POLY_CZT
#define TIFALIBS_POLY_CZT

#include "../math/rpow.hpp"
#include "poly.hpp"

namespace tifa_libs::math {

// @brief Chirp Z-Transform
// @return {f(c^0), f(c^1), ..., f(c^{m-1})}
template <class T, class mint = typename T::value_type>
inline poly<T> poly_czt(poly<T> const &f, mint c, u64 m = (u64)-1) {
  constexpr static u64 mod = mint::mod();
  static rpow rp;
  rp.reset(c.val(), mod);
  if (m == (u64)-1) m = f.size();
  if (f.data().empty() || !m) return poly<T>{};
  usz n = f.size();
  poly<T> cc(n + m - 1), g(n);
  for (u64 i = 0; i < n + m - 1; ++i) cc[n + m - 2 - i] = rp((i - 1) * i / 2 % (mod - 1));
  for (u64 i = 0; i < n; ++i) g[i] = rp(mod - 1 - (i * (i - 1) / 2) % (mod - 1)) * f[i];
  cc.conv(g, n + m);
  poly<T> ans(m);
  for (u64 i = 0; i < m; ++i) ans[i] = cc[n + m - 2 - i] * rp(mod - 1 - (i * (i - 1) / 2) % (mod - 1));
  return ans;
}

}  // namespace tifa_libs::math

#endif