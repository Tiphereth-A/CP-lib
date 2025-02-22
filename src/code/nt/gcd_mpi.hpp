#ifndef TIFALIBS_MATH_GCD_MPI
#define TIFALIBS_MATH_GCD_MPI

#include "../math/mpi.hpp"
#include "../math/qpow.hpp"
#include "../nt/gcd.hpp"

namespace tifa_libs::math {
namespace gcd_mpi_impl_ {
// @return {x, y} s.t. a = 2^x 5^y
CEXP ptti shrink(u32 a) NE {
  assert(a > 0);
  const int x = std::countr_zero(a);
  a >>= x;
  // clang-format off
  return {x, a == 1 ? 0 : a == 5 ? 1 : a == 25 ? 2 : a == 125 ? 3 : a == 625 ? 4 : a == 3125 ? 5 : a == 15625 ? 6 : a == 78125 ? 7 : a == 390625 ? 8 : 9};
  // clang-format on
}
CEXP ptti shrink(mpi& a) NE {
  if (assert(!a.is_neg()); a.empty()) return {0, 0};
  ptti res{0, 0};
  while (true) {
    const u32 g = gcd(mpi::D, a[0]);
    if (g == 1) break;
    if (g != mpi::D) a *= mpi::D / g;
    a.erase(a.begin());
    const auto s = shrink(g);
    res.first += s.first, res.second += s.second;
  }
  return res;
}
}  // namespace gcd_mpi_impl_

template <bool FAST = true>
CEXP mpi gcd_mpi(mpi a, mpi b) NE {
  a.set_neg(false), b.set_neg(false);
  if CEXP (FAST)
    if (max(a.size(), b.size()) <= 2) return gcd(a.to_i64(), b.to_i64());
  if (a.empty()) return b;
  if (b.empty()) return a;
  const ptti s = gcd_mpi_impl_::shrink(a), t = gcd_mpi_impl_::shrink(b);
  if (a < b) swap(a, b);
  while (true) {
    if (b.empty()) break;
    if CEXP (FAST)
      if (a.size() <= 2) break;
    if (a = a - b; !a.empty())
      while (true) {
        const u32 g = gcd(a[0], mpi::D);
        if (g == 1) break;
        if (g != mpi::D) a *= mpi::D / g;
        a.erase(a.begin());
      }
    if (a < b) swap(a, b);
  }
  assert(a >= b);
  mpi g;
  if CEXP (FAST) g = b.empty() ? a : gcd(a.to_i64(), b.to_i64());
  else g = a;
  const u32 e2 = (u32)min(s.first, t.first), e5 = (u32)min(s.second, t.second);
  if (e2) g *= qpow(mpi{2}, e2);
  if (e5) g *= qpow(mpi{5}, e5);
  return g;
}

}  // namespace tifa_libs::math

#endif