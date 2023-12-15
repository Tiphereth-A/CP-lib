#ifndef TIFALIBS_MATH_EXEUCLID
#define TIFALIBS_MATH_EXEUCLID

#include "../util/util.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

namespace exeuclid_impl_ {

template <class T>
T solve_(i64 p, i64 q, i64 r, i64 l, T a, T b) {
#pragma GCC diagnostic ignored "-Wfloat-conversion"
  auto div = [](i64 a, i64 b, i64 c, i64 d) -> i64 { return (1.l * a * b + c) / d; };
#pragma GCC diagnostic warning "-Wfloat-conversion"
  if (!l) return {};
  if (p >= q) return solve_(p % q, q, r, l, a, qpow(a, u64(p / q), T{}) * b);
  i64 m = div(l, p, r, q);
  if (!m) return qpow(b, (u64)l, T{});
  i64 cnt = l - div(q, m, -r - 1, p);
  return qpow(b, u64((q - r - 1) / p), T{}) * a * solve_(q, p, (q - r - 1) % p, m - 1, b, a) * qpow(b, (u64)cnt, T{});
}

}  // namespace exeuclid_impl_

// consider line s: y = (p * x + r) / q, 0 < x <= l
// result will add a when s cross with horizontal line
// result will add b when s cross with vertical line
template <class Node>
Node exeuclid(i64 p, i64 q, i64 r, i64 l, Node const &a, Node const &b) { return qpow(a, u64(r / q), Node{}) * exeuclid_impl_::solve_(p, q, r % q, l, a, b); }

}  // namespace tifa_libs::math

#endif