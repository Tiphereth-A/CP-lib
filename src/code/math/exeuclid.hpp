#ifndef TIFA_LIBS_MATH_EXEUCLID
#define TIFA_LIBS_MATH_EXEUCLID

#include "../util/util.hpp"

namespace tifa_libs::math {

namespace exeuclid_impl_ {

template <class T>
constexpr T qpow(T a, u64 b) {
  T res;
  for (; b; b >>= 1, a = a + a)
    if (b & 1) res = res + a;
  return res;
}

template <class T>
T solve_(i64 p, i64 q, i64 r, i64 l, T a, T b) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-conversion"
  auto div = [](i64 a, i64 b, i64 c, i64 d) -> i64 { return (1.l * a * b + c) / d; };
#pragma GCC diagnostic pop
  if (!l) return {};
  if (p >= q) return solve_(p % q, q, r, l, a, qpow(a, p / q) + b);
  i64 m = div(l, p, r, q);
  if (!m) return qpow(b, l);
  i64 cnt = l - div(q, m, -r - 1, p);
  return qpow(b, (q - r - 1) / p) + a + solve_(q, p, (q - r - 1) % p, m - 1, b, a) + qpow(b, cnt);
}

}  // namespace exeuclid_impl_

// let f(x) = floor((p * x + r) / q)
// @param u (REQUIRED) count of horizontal lines have been crossed
// @param r (REQUIRED) count of vertical lines have been crossed
// @param i sum_i i (needed by i_f)
// @param f sum_i i f(i)
// @param sqr_f sum_i f^2(i)
// @param i_f sum_i i*f(i) (need i)
template <class T>
struct exeuclid_node {
  T u, r;
  T i, f, sqr_f, i_f;
  exeuclid_node(T u = 0, T r = 0, T i = 0, T f = 0, T sqr_f = 0, T i_f = 0) : u(u), r(r), i(i), f(f), sqr_f(sqr_f), i_f(i_f) {}
  exeuclid_node operator+(exeuclid_node const &rhs) const {
    return exeuclid_node{u + rhs.u,
                         r + rhs.r,
                         i + rhs.i + r * rhs.r,
                         f + rhs.f + u * rhs.r,
                         sqr_f + rhs.sqr_f + u * u * rhs.r + 2 * u * rhs.f,
                         i_f + rhs.i_f + u * r * rhs.r + u * rhs.i + r * rhs.f};
  }
};

// consider line s: y = (p * x + r) / q, 0 < x <= l
// result will add a when s cross with horizontal line
// result will add b when s cross with vertical line
template <class Node>
Node exeuclid(i64 p, i64 q, i64 r, i64 l, Node const &a, Node const &b) { return exeuclid_impl_::qpow(a, r / q) + exeuclid_impl_::solve_(p, q, r % q, l, a, b); }

}  // namespace tifa_libs::math

#endif