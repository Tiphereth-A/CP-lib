#ifndef TIFALIBS_POLY_POLY_MPE
#define TIFALIBS_POLY_POLY_MPE

#include "poly_inv.hpp"
#include "poly_shr.hpp"

namespace tifa_libs::math {

// Multi-point evaluation based on Tellegen's Principle
// @return {f(a[0]), f(a[1]), ..., f(a.back())}
template <class poly>
constexpr poly poly_mpe(poly f, poly a) {
  class SegTree {
    vec<poly> t;

    constexpr void init_(poly const &a, u32 k, u32 l, u32 r) {
      if (l == r) {
        t[k] = poly{1, -a[l]};
        return;
      }
      u32 m = l + (r - l) / 2;
      init_(a, k * 2, l, m);
      init_(a, k * 2 + 1, m + 1, r);
      t[k] = t[k * 2] * t[k * 2 + 1];
    }
    static constexpr poly mult(poly const &f, poly g) {
      u32 m = g.size();
      g.reverse();
      g.conv(f);
      g = poly_shr(g, m - 1);
      g.resize(f.size());
      return g;
    }
    constexpr void calc_(poly f, poly &res, u32 k, u32 l, u32 r) const {
      f.resize(r - l + 1);
      if (l == r) {
        res[l] = f[0];
        return;
      }
      u32 m = l + (r - l) / 2;
      calc_(mult(f, t[k * 2 + 1]), res, k * 2, l, m);
      calc_(mult(f, t[k * 2]), res, k * 2 + 1, m + 1, r);
    }

   public:
    explicit constexpr SegTree(poly const &a) : t(a.size() * 4) { init_(a, 1, 0, a.size() - 1); }

    constexpr poly operator()(poly const &f) const {
      poly res(f.size());
      calc_(mult(f, poly_inv(t[1])), res, 1, 0, t.size() / 4 - 1);
      return res;
    }
  };

  u32 n = f.size(), m = a.size();
  f.resize(std::max(n, m));
  a.resize(std::max(n, m));
  auto _ = SegTree(a)(f);
  _.resize(m);
  return _;
}

}  // namespace tifa_libs::math

#endif