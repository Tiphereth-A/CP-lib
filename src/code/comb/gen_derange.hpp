#ifndef TIFALIBS_COMB_GEN_DERANGE
#define TIFALIBS_COMB_GEN_DERANGE

#include "../math/mul_mod_u.hpp"

namespace tifa_libs::math {

// (derangement) !i for i=0..n-1
constexpr vec<u64> gen_derange(u32 n, u64 mod) {
  vec<u64> d{0, mod > 1};
  if (n > 2) d.reserve(n);
  else {
    d.resize(n);
    return d;
  }
  for (u32 i = 2; i < n; ++i) d.push_back(mul_mod_u(i, d[i - 1] + d[i - 2], mod));
  return d;
}
template <class mint>
constexpr vec<mint> gen_derange(u32 n) {
  vec<mint> d(n);
  auto _ = gen_derange(n, mint::mod());
  for (u32 i = 0; i < n; ++i) d[i] = _[i];
  return d;
}

}  // namespace tifa_libs::math

#endif