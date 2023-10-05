#ifndef TIFALIBS_POLY_CONV_3NTT
#define TIFALIBS_POLY_CONV_3NTT

#include "../math/mul_mod_u.hpp"
#include "../util/util.hpp"
#include "conv_ntt.hpp"

namespace tifa_libs::math {

// 167772161, 469762049, 754974721
template <class mint0, class mint1, class mint2>
inline vec<u64> conv_3ntt(vec<u64> const &l, vec<u64> const &r, u64 mod, size_t ans_size) {
  static constexpr u32 m0 = mint0::mod();
  static constexpr u32 m1 = mint1::mod();
  static constexpr u32 m2 = mint2::mod();
  static const u32 r01 = mint1(m0).inv().val();
  static const u32 r02 = mint2(m0).inv().val();
  static const u32 r12 = mint2(m1).inv().val();
  static const u32 r02r12 = (u32)mul_mod_u(r02, r12, m2);
  static const u64 w1 = m0 % mod;
  static const u64 w2 = mul_mod_u(m0, m1, mod);

  vec<mint0> d0 = conv_ntt<mint0>(l, r, ans_size);
  vec<mint1> d1 = conv_ntt<mint1>(l, r, ans_size);
  vec<mint2> d2 = conv_ntt<mint2>(l, r, ans_size);

  vec<u64> ret(ans_size);
  for (size_t i = 0; i < ans_size; ++i) {
    u64 n1 = d1[i].val(), n2 = d2[i].val(), a = d0[i].val();
    u64 b = mul_mod_u((n1 + m1 - a), r01, m1), c = mul_mod_u(n2 + m2 - a, r02r12, m2) + mul_mod_u(m2 - b, r12, m2);
    ret[i] = (a + mul_mod_u(b, w1, mod) + mul_mod_u(c % m2, w2, mod)) % mod;
  }
  return ret;
}
template <class mint0, class mint1, class mint2>
inline vec<u64> conv_3ntt(vec<u64> const &l, vec<u64> const &r, u64 mod) { return conv_3ntt<mint0, mint1, mint2>(l, r, mod, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif