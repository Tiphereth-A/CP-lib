#ifndef TIFALIBS_MATH_GCD_MPI
#define TIFALIBS_MATH_GCD_MPI

#include "../util/util.hpp"
#include "gcd128.hpp"
#include "mpi.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

namespace gcd_mpi_impl_ {

// @return {x, y} s.t. a = 2^x 5^y
constexpr ptt<i32> shrink(u32 a) {
  assert(a > 0);
  int x = bit::cntr0(a);
  a >>= x;
  // clang-format off
  return {x, a == 1 ? 0 : a == 5 ? 1 : a == 25 ? 2 : a == 125 ? 3 : a == 625 ? 4 : a == 3125 ? 5 : a == 15625 ? 6 : a == 78125 ? 7 : a == 390625 ? 8 : 9};
  // clang-format on
}

inline ptt<i32> shrink(mpi& a) {
  assert(!a.is_neg());
  if (a.data().empty()) return {0, 0};
  ptt<i32> res{0, 0};
  while (true) {
    u32 g = std::gcd(mpi::digit(), a.data()[0]);
    if (g == 1) break;
    if (g != mpi::digit()) a *= mpi::digit() / g;
    a.data().erase(begin(a.data()));
    auto s = shrink(g);
    res.first += s.first, res.second += s.second;
  }
  return res;
}

}  // namespace gcd_mpi_impl_

template <bool FAST = true>
mpi gcd_mpi(mpi a, mpi b) {
  a.set_neg(false), b.set_neg(false);
  if constexpr (FAST)
    if (std::max(a.data().size(), b.data().size()) <= 4) return gcd_128(a.to_i128(), b.to_i128());
  if (a.data().empty()) return b;
  if (b.data().empty()) return a;
  ptt<i32> s = gcd_mpi_impl_::shrink(a), t = gcd_mpi_impl_::shrink(b);
  if (a < b) std::swap(a, b);
  while (true) {
    if (b.data().empty()) break;
    if constexpr (FAST)
      if (a.data().size() <= 4) break;
    a = a - b;
    if (!a.data().empty())
      while (true) {
        u32 g = std::gcd(a.data()[0], mpi::digit());
        if (g == 1) break;
        if (g != mpi::digit()) a *= mpi::digit() / g;
        a.data().erase(begin(a.data()));
      }
    if (a < b) std::swap(a, b);
  }
  assert(a >= b);
  mpi g;
  if constexpr (FAST) g = b.data().empty() ? a : gcd_128(a.to_i128(), b.to_i128());
  else g = a;
  u32 e2 = (u32)std::min(s.first, t.first), e5 = (u32)std::min(s.second, t.second);
  if (e2) g *= qpow(mpi{2}, e2);
  if (e5) g *= qpow(mpi{5}, e5);
  return g;
}

}  // namespace tifa_libs::math

#endif