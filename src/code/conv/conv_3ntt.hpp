#ifndef TIFALIBS_CONV_CONV_3NTT
#define TIFALIBS_CONV_CONV_3NTT

#include "../math/mul_mod_u.hpp"
#include "conv_dft.hpp"
#include "ntt32.hpp"

namespace tifa_libs::math {

// 167772161, 469762049, 754974721
template <class mint0, class mint1, class mint2>
constexpr vec<u64> conv_3ntt_u64(std::tuple<NTT32<mint0>, NTT32<mint1>, NTT32<mint2>> &ntt3, vec<u64> const &l, vec<u64> const &r, u64 mod, u32 ans_size = 0) {
  constexpr u32 m0 = mint0::mod(), m1 = mint1::mod(), m2 = mint2::mod();
  const u32 r01 = mint1(m0).inv().val(), r02 = mint2(m0).inv().val(), r12 = mint2(m1).inv().val(), r02r12 = (u32)mul_mod_u(r02, r12, m2);
  const u64 w1 = m0 % mod, w2 = mul_mod_u(m0, m1, mod);

  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  auto &[ntt0, ntt1, ntt2] = ntt3;

  vec<mint0> d0 = conv_dft_u64<NTT32<mint0>, mint0>(ntt0, l, r, ans_size);
  vec<mint1> d1 = conv_dft_u64<NTT32<mint1>, mint1>(ntt1, l, r, ans_size);
  vec<mint2> d2 = conv_dft_u64<NTT32<mint2>, mint2>(ntt2, l, r, ans_size);

  vec<u64> ret(ans_size);
  for (u32 i = 0; i < ans_size; ++i) {
    u64 n1 = d1[i].val(), n2 = d2[i].val(), a = d0[i].val();
    u64 b = mul_mod_u((n1 + m1 - a), r01, m1), c = mul_mod_u(n2 + m2 - a, r02r12, m2) + mul_mod_u(m2 - b, r12, m2);
    ret[i] = (a + mul_mod_u(b, w1, mod) + mul_mod_u(c % m2, w2, mod)) % mod;
  }
  return ret;
}
template <class mint, class mint0, class mint1, class mint2>
constexpr vec<mint> conv_3ntt(std::tuple<NTT32<mint0>, NTT32<mint1>, NTT32<mint2>> &ntt3, vec<mint> const &l, vec<mint> const &r, u32 ans_size = 0) {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  if (ans_size < 32) return conv_naive(l, r, ans_size);
  vec<u64> l_(l.size()), r_(r.size());
  for (u32 i = 0; i < l.size(); ++i) l_[i] = l[i].val();
  for (u32 i = 0; i < r.size(); ++i) r_[i] = r[i].val();
  vec<u64> _ = conv_3ntt_u64(ntt3, l_, r_, mint::mod(), ans_size);
  vec<mint> res(_.size());
  for (u32 i = 0; i < _.size(); ++i) res[i] = _[i];
  return res;
}

}  // namespace tifa_libs::math

#endif