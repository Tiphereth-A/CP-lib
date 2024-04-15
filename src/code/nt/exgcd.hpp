#ifndef TIFALIBS_MATH_EXGCD
#define TIFALIBS_MATH_EXGCD

#include "../util/traits.hpp"

namespace tifa_libs::math {

// Binary exgcd
template <uint_c U>
constexpr auto exgcd(U a, U b) {
  using T = to_sint_t<U>;
  if (!a) return std::make_tuple(b, (T)0, (T) !!b);
  if (!b) return std::make_tuple(a, (T)1, (T)0);
  bool f = 0;
  if (a > b) std::swap(a, b), f = 1;
  auto r = std::__countr_zero(a | b);
  a >>= r, b >>= r;
  T x = (T)a, y = (T)b;
  T s = 1, t = 0, u = 0, v = 1;
  while (x) {
    while (!(x & 1)) {
      x /= 2;
      if (!((s | t) & 1)) s /= 2, t /= 2;
      else s = std::midpoint(s, (T)b), t = std::midpoint(t, -(T)a);
    }
    while (!(y & 1)) {
      y /= 2;
      if (!((u | v) & 1)) u /= 2, v /= 2;
      else u = std::midpoint(u, (T)b), v = std::midpoint(v, -(T)a);
    }
    if (x >= y) x -= y, s -= u, t -= v;
    else y -= x, u -= s, v -= t;
  }
  if (f) std::swap(a, b), std::swap(u, v), std::swap(s, t);
  if (y > 1) a /= (U)y, b /= (U)y;
  if (a && (U)abs(v) >= a) {
    T _ = v / (T)a;
    v -= _ * (T)a, u += _ * (T)b;
  }
  if (b && (U)abs(u) >= b) {
    T _ = u / (T)b;
    u -= _ * (T)b, v += _ * (T)a;
  }
  if (T u_ = u + (T)b, v_ = v - (T)a; abs(u_) + abs(v_) <= abs(u) + abs(v)) u = u_, v = v_;
  if (T u_ = u - (T)b, v_ = v + (T)a; abs(u_) + abs(v_) <= abs(u) + abs(v)) u = u_, v = v_;
  return std::make_tuple(U(y << r), u, v);
}
// @return tuple(g, x, y) s.t. g = gcd(a, b), xa + yb = g, |x| + |y| is the minimal (primary) and x <= y (secondarily)
template <sint_c T>
constexpr auto exgcd(T a, T b) {
  using U = to_uint_t<T>;
  if (auto [x, y] = std::minmax(a, b); x >= 0 && y <= T(U(-1) / 16)) return exgcd((U)a, (U)b);
  T s = 1, t = 0, u = 0, v = 1;
  while (b) {
    T c = a / b;
    std::tie(s, t, u, v, a, b) = std::make_tuple(u, v, s - u * c, t - v * c, b, a - b * c);
  }
  return std::make_tuple((U)a, s, t);
}

}  // namespace tifa_libs::math

#endif