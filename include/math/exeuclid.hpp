#ifndef TIFALIBS_MATH_EXEUCLID
#define TIFALIBS_MATH_EXEUCLID

#include "qpow.hpp"

namespace tifa_libs::math {

// consider line s: y = (p * x + r) / q, 0 < x <= l
// result will add a when s cross with horizontal line
// result will add b when s cross with vertical line
template <class TIFA>
CEXP TIFA exeuclid(i64 p, i64 q, i64 r, i64 l, TIFA CR a, TIFA CR b) NE {
#pragma GCC diagnostic ignored "-Wfloat-conversion"
  auto div = [](i64 a, i64 b, i64 c, i64 d) NE -> i64 { return (1.l * a * b + c) / d; };
#pragma GCC diagnostic warning "-Wfloat-conversion"
  auto f = [&](auto&& f, i64 p, i64 q, i64 r, i64 l, cT_(TIFA) a, cT_(TIFA) b) NE -> TIFA {
    if (!l) return {};
    if (p >= q) return f(f, p % q, q, r, l, a, qpow(a, u64(p / q), TIFA{}) * b);
    const i64 m = div(l, p, r, q);
    if (!m) return qpow(b, (u64)l, TIFA{});
    const i64 cnt = l - div(q, m, -r - 1, p);
    return qpow(b, u64((q - r - 1) / p), TIFA{}) * a * f(f, q, p, (q - r - 1) % p, m - 1, b, a) * qpow(b, (u64)cnt, TIFA{});
  };
  return qpow(a, u64(r / q), TIFA{}) * f(f, p, q, r % q, l, a, b);
}

}  // namespace tifa_libs::math

#endif