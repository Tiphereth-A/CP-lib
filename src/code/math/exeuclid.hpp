#ifndef TIFA_LIBS_MATH_EXEUCLID
#define TIFA_LIBS_MATH_EXEUCLID

#include "../util/util.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

namespace exeuclid_impl_ {

template <class T>
T solve_(i64 p, i64 q, i64 r, i64 l, T a, T b) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-conversion"
  auto div = [](i64 a, i64 b, i64 c, i64 d) -> i64 { return (1.l * a * b + c) / d; };
#pragma GCC diagnostic pop
  if (!l) return {};
  if (p >= q) return solve_(p % q, q, r, l, a, qpow(a, u64(p / q)) * b);
  i64 m = div(l, p, r, q);
  if (!m) return qpow(b, (u64)l);
  i64 cnt = l - div(q, m, -r - 1, p);
  return qpow(b, u64((q - r - 1) / p)) * a * solve_(q, p, (q - r - 1) % p, m - 1, b, a) * qpow(b, (u64)cnt);
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
  friend exeuclid_node operator*(exeuclid_node const &l, exeuclid_node const &r) {
    return {l.u + r.u,
            l.r + r.r,
            l.i + r.i + l.r * r.r,
            l.f + r.f + l.u * r.r,
            l.sqr_f + r.sqr_f + l.u * l.u * r.r + 2 * l.u * r.f,
            l.i_f + r.i_f + l.u * l.r * r.r + l.u * r.i + l.r * r.f};
  }
};

// consider line s: y = (p * x + r) / q, 0 < x <= l
// result will add a when s cross with horizontal line
// result will add b when s cross with vertical line
template <class Node>
Node exeuclid(i64 p, i64 q, i64 r, i64 l, Node const &a, Node const &b) { return qpow(a, u64(r / q)) * exeuclid_impl_::solve_(p, q, r % q, l, a, b); }

}  // namespace tifa_libs::math

#endif