#ifndef TIFALIBS_POLY_INTERP
#define TIFALIBS_POLY_INTERP

#include "poly_deriv.hpp"
#include "poly_mpe.hpp"

namespace tifa_libs::math {

// Lagrange interpolation in O(n \log^2 n)
// @return f s.t. f(x[i]) = y[i]
template <class T>
inline poly<T> poly_interp(poly<T> const &x, poly<T> const &y) {
  class SegTree {
    constexpr void init_(poly<T> const &a, size_t k, size_t l, size_t r) {
      if (l == r) {
        t[k] = poly<T>{-a[l], 1};
        return;
      }
      size_t m = l + (r - l) / 2;
      init_(a, k * 2, l, m);
      init_(a, k * 2 + 1, m + 1, r);
      t[k] = t[k * 2] * t[k * 2 + 1];
    }
    constexpr poly<T> calc_(poly<T> const &f, size_t k, size_t l, size_t r) const {
      if (l == r) return poly<T>{f[l]};
      size_t m = l + (r - l) / 2;
      return calc_(f, k * 2, l, m) * t[2 * k + 1] + calc_(f, k * 2 + 1, m + 1, r) * t[2 * k];
    }

  public:
    vec<poly<T>> t;

    explicit constexpr SegTree(poly<T> const &a):
      t(a.size() * 4) { init_(a, 1, 0, a.size() - 1); }

    constexpr poly<T> operator()(poly<T> const &f) const { return calc_(f, 1, 0, t.size() / 4 - 1); }
  };

  assert(x.size() == y.size());
  size_t n = x.size();
  SegTree sgt(x);
  poly<T> t = poly_mpe(poly_deriv(sgt.t[1]), x);
  for (size_t i = 0; i < n; ++i) t[i] = y[i] * t[i].inv();
  return sgt(t);
}

}  // namespace tifa_libs::math

#endif