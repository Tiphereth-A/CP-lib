#ifndef TIFALIBS_POLY_MPE_FPS
#define TIFALIBS_POLY_MPE_FPS

#include "inv_fps.hpp"
#include "shr_fps.hpp"

namespace tifa_libs::math {

// Multi-point evaluation based on Tellegen's Principle
// @return {f(a[0]), f(a[1]), ..., f(a.back())}
template <class mint, class ccore>
CEXP poly<mint, ccore> mpe_fps(poly<mint, ccore> f, poly<mint, ccore> a) {
  using poly_t = poly<mint, ccore>;
  class SegTree {
    vec<poly_t> t;
    CEXP void init_(cT_(poly_t) a, u32 k, u32 l, u32 r) {
      if (l == r) {
        t[k] = poly_t{1, -a[l]};
        return;
      }
      u32 m = l + (r - l) / 2;
      init_(a, k * 2, l, m), init_(a, k * 2 + 1, m + 1, r);
      t[k] = t[k * 2] * t[k * 2 + 1];
    }
    static CEXP poly_t mult(cT_(poly_t) f, poly_t g) {
      const u32 m = g.size();
      g.reverse(), g.conv(f), g = shr_fps(g, m - 1), g.resize(f.size());
      return g;
    }
    CEXP void calc_(poly_t f, poly_t &res, u32 k, u32 l, u32 r) const {
      f.resize(r - l + 1);
      if (l == r) {
        res[l] = f[0];
        return;
      }
      const u32 m = l + (r - l) / 2;
      calc_(mult(f, t[k * 2 + 1]), res, k * 2, l, m);
      calc_(mult(f, t[k * 2]), res, k * 2 + 1, m + 1, r);
    }

   public:
    explicit CEXP SegTree(poly_t CR a) : t(a.size() * 4) { init_(a, 1, 0, a.size() - 1); }
    CEXP poly_t operator()(poly_t CR f) const {
      poly_t res(f.size());
      calc_(mult(f, inv_fps(t[1])), res, 1, 0, t.size() / 4 - 1);
      return res;
    }
  };

  const u32 n = f.size(), m = a.size();
  f.resize(max(n, m)), a.resize(max(n, m));
  auto _ = SegTree(a)(f);
  _.resize(m);
  return _;
}

}  // namespace tifa_libs::math

#endif