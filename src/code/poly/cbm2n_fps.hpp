#ifndef TIFALIBS_POLY_CBM2N_FPS
#define TIFALIBS_POLY_CBM2N_FPS

#include "divmod_fps.hpp"

namespace tifa_libs::math {

// @return b s.t. $f(x) = \sum_{i=0}^{n-1} b_i \prod_{j=0}^{i-1}(x - p_j)$
template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto cbm2n_fps(poly<ccore, mint, args...> CR f, vec<mint> CR p) NE {
  using poly_t = poly<ccore, mint, args...>;
  const u32 n = (u32)p.size();
  assert(f.size() == n);
  const u32 m = std::bit_ceil(n);
  vec<poly_t> s(2 * m, poly_t{0, 1});
  flt_ (u32, i, 0, m)
    if (i < n) s[m + i][0] = -p[i];
  for (u32 i = m - 1; i; --i) {
    if (std::has_single_bit(i + 1)) continue;
    s[i] = s[2 * i] * s[2 * i + 1];
  }
  s[1] = f;
  flt_ (u32, i, 1, m) std::tie(s[2 * i + 1], s[2 * i]) = divmod_fps(s[i], s[2 * i]);
  poly_t b(n);
  flt_ (u32, i, 0, n) b[i] = s[m + i][0];
  return b;
}

}  // namespace tifa_libs::math

#endif