#ifndef TIFALIBS_MATH_PFACTORS
#define TIFALIBS_MATH_PFACTORS

#include "../math/mul_mod_u.hpp"
#include "../rand/gen.hpp"
#include "is_prime.hpp"

namespace tifa_libs::math {
namespace pfactors_impl_ {
class PollardRho {
  rand::Gen<std::uniform_int_distribution<u64>> e;

  constexpr u64 rho(u64 n) {
    e.set_range(2, n - 1);
    auto f = [n, r = e()](u64 x) { return (mul_mod_u(x, x, n) + r) % n; };
    u64 g = 1, x = 0, y = e(), yy = 0;
    const u32 LIM = 128;
    for (u64 r = 1, q = 1; g == 1; r *= 2) {
      x = y;
      for (u64 i = 0; i < r; ++i) y = f(y);
      for (u64 k = 0; g == 1 && k < r; k += LIM) {
        yy = y;
        for (u64 i = 0; i < LIM && i < r - k; ++i) q = mul_mod_u(q, (x + (n - (y = f(y)))) % n, n);
        g = std::gcd(q, n);
      }
    }
    if (g == n) do {
        g = std::gcd((x + (n - (yy = f(yy)))) % n, n);
      } while (g == 1);
    return g == n ? rho(n) : g;
  }

 public:
  explicit constexpr PollardRho() : e() {}

  constexpr void operator()(u64 n, std::map<u64, u32> &ans) {
    if (n < 2) return;
    if (is_prime(n)) {
      ++ans[n];
      return;
    }
    auto g = rho(n);
    (*this)(n / g, ans);
    (*this)(g, ans);
  }
};
}  // namespace pfactors_impl_

inline std::map<u64, u32> pfactors(u64 n) {
  std::map<u64, u32> ans;
  if (n < 2) return ans;
  if (~n & 1) n >>= (ans[2] = (u32)std::countr_zero(n));
  pfactors_impl_::PollardRho()(n, ans);
  return ans;
}

}  // namespace tifa_libs::math

#endif