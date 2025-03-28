#ifndef TIFALIBS_POLY_INTERP_FPS
#define TIFALIBS_POLY_INTERP_FPS

#include "deriv_fps.hpp"
#include "mpe_fps.hpp"

namespace tifa_libs::math {

// Lagrange interpolation in O(n \log^2 n)
// @return f s.t. f(x[i]) = y[i]
template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto interp_fps(poly<ccore, mint, args...> CR x, poly<ccore, mint, args...> CR y) NE {
  using poly_t = poly<ccore, mint, args...>;
  class SegTree {
    CEXP void init_(poly_t CR a, u32 k, u32 l, u32 r) NE {
      if (l == r) return void(t[k] = poly_t{-a[l], 1});
      const u32 m = l + (r - l) / 2;
      init_(a, k * 2, l, m), init_(a, k * 2 + 1, m + 1, r), t[k] = t[k * 2] * t[k * 2 + 1];
    }
    CEXP poly_t calc_(cT_(poly_t) f, u32 k, u32 l, u32 r) CNE {
      if (l == r) return {f[l]};
      const u32 m = l + (r - l) / 2;
      return calc_(f, k * 2, l, m) * t[2 * k + 1] + calc_(f, k * 2 + 1, m + 1, r) * t[2 * k];
    }

   public:
    vec<poly_t> t;
    CEXPE SegTree(poly_t CR a) NE : t(a.size() * 4) { init_(a, 1, 0, u32(a.size() - 1)); }
    CEXP poly_t operator()(poly_t CR f) CNE { return calc_(f, 1, 0, u32(t.size() / 4 - 1)); }
  };

  assert(x.size() == y.size());
  const u32 n = (u32)x.size();
  SegTree sgt(x);
  poly_t t = mpe_fps(deriv_fps(sgt.t[1]), x);
  flt_ (u32, i, 0, n) t[i] = y[i] * t[i].inv();
  return sgt(t);
}

}  // namespace tifa_libs::math

#endif