#ifndef TIFALIBS_MATH_MONTGOMERY
#define TIFALIBS_MATH_MONTGOMERY

#include "../util/util.hpp"

namespace tifa_libs::math {

struct Montgomery {
  u32 mod;
  u32 mod2;   // 2 * mod
  u32 n_inv;  // n_inv * mod == -1 (mod 2^32)
  u32 r;      // 2^32 % mod
  u32 r2;     // (2^32) ^ 2 % mod

  constexpr explicit Montgomery(u32 mod = 998244353) : mod(mod), mod2(mod * 2), n_inv(1), r((1ULL << 32) % mod), r2(r * u64(r) % mod) {
    assert(mod % 2);
    assert(mod < (1 << 30));
    for (int i = 0; i < 5; ++i) n_inv *= 2u + n_inv * mod;
    assert(n_inv * mod == -1u);
  }

  constexpr u32 shrink(u32 val) const { return std::min(val, val - mod); }
  constexpr u32 shrink2(u32 val) const { return std::min(val, val - mod2); }
  constexpr u32 shrink_n(u32 val) const { return std::min(val, val + mod); }
  constexpr u32 shrink2_n(u32 val) const { return std::min(val, val + mod2); }

  // a * b should be in [0, 2**32 * mod)
  // result in [0, 2 * mod)   <false>
  // result in [0, mod)       <true>
  template <bool strict = false>
  constexpr u32 mul(u32 a, u32 b) const {
    u64 val = u64(a) * b;
    u32 res = (val + u32(val) * n_inv * u64(mod)) >> 32;
    if constexpr (strict) res = shrink(res);
    return res;
  }
};

}  // namespace tifa_libs::math

#endif