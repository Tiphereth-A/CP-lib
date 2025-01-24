#ifndef TIFALIBS_POLY_MPE_FPS
#define TIFALIBS_POLY_MPE_FPS

#include "inv_fps.hpp"
#include "shr_fps.hpp"

namespace tifa_libs::math {

// Multi-point evaluation based on Tellegen's Principle
// @return {f(a[0]), f(a[1]), ..., f(a.back())}
template <template <class... Ts> class ccore, class mint, class... args>
CEXP auto mpe_fps(poly<ccore, mint, args...> f, poly<ccore, mint, args...> a) NE {
  using poly_t = poly<ccore, mint, args...>;
  class SegTree {
    vec<poly_t> t;
    CEXP void init_(cT_(poly_t) a, u32 k, u32 l, u32 r) NE {
      if (l == r) {
        t[k] = poly_t{1, -a[l]};
        return;
      }
      const u32 m = l + (r - l) / 2;
      init_(a, k * 2, l, m), init_(a, k * 2 + 1, m + 1, r), t[k] = t[k * 2] * t[k * 2 + 1];
    }
    static CEXP poly_t mult(cT_(poly_t) f, poly_t g) NE {
      const u32 m = (u32)g.size();
      g.reverse(), g.conv(f);
      g = shr_fps(g, m - 1);
      g.resize(f.size());
      return g;
    }
    CEXP void calc_(poly_t f, poly_t &res, u32 k, u32 l, u32 r) CNE {
      f.resize(r - l + 1);
      if (l == r) return void(res[l] = f[0]);
      const u32 m = l + (r - l) / 2;
      calc_(mult(f, t[k * 2 + 1]), res, k * 2, l, m), calc_(mult(f, t[k * 2]), res, k * 2 + 1, m + 1, r);
    }

   public:
    CEXPE SegTree(poly_t CR a) NE : t(a.size() * 4) { init_(a, 1, 0, (u32)a.size() - 1); }
    CEXP poly_t operator()(poly_t CR f) CNE {
      poly_t res((u32)f.size());
      calc_(mult(f, inv_fps(t[1])), res, 1, 0, u32(t.size() / 4 - 1));
      return res;
    }
  };

  const u32 n = (u32)f.size(), m = (u32)a.size();
  f.resize(max(n, m)), a.resize(max(n, m));
  auto _ = SegTree(a)(f);
  return _.pre(m);
}

}  // namespace tifa_libs::math

#endif