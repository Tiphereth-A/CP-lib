#ifndef TIFALIBS_POLY_POLY_CBM2N
#define TIFALIBS_POLY_POLY_CBM2N

#include "poly_divmod.hpp"

namespace tifa_libs::math {

// @return b s.t. $f(x) = \sum_{i=0}^{n-1} b_i \prod_{j=0}^{i-1}(x - p_j)$
template <class T, class mint = typename T::value_type>
constexpr poly<T> poly_cbm2n(poly<T> const &f, vec<mint> const &p) {
  u32 n = (u32)p.size();
  assert(f.size() == n);
  u32 m = std::bit_ceil(n);
  vec<poly<T>> s(2 * m, poly<T>{0, 1});
  for (u32 i = 0; i < m; ++i)
    if (i < n) s[m + i][0] = -p[i];
  for (u32 i = m - 1; i; --i) {
    if (std::has_single_bit(i + 1)) continue;
    s[i] = s[2 * i] * s[2 * i + 1];
  }
  s[1] = f;
  for (u32 i = 1; i < m; ++i) std::tie(s[2 * i + 1], s[2 * i]) = poly_divmod(s[i], s[2 * i]);
  poly<T> b(n);
  for (u32 i = 0; i < n; ++i) b[i] = s[m + i][0];
  return b;
}

}  // namespace tifa_libs::math

#endif