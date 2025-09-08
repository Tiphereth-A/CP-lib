#ifndef TIFALIBS_CONV_CONV_3NTT
#define TIFALIBS_CONV_CONV_3NTT

#include "conv_dft.hpp"
#include "conv_naive_mod.hpp"
#include "ntt.hpp"

namespace tifa_libs::math {

// 167772161, 469762049, 754974721
template <class mint0, class mint1, class mint2>
CEXP vecuu conv_3ntt_u64(ntt<mint0> &ntt0, ntt<mint1> &ntt1, ntt<mint2> &ntt2, vecuu CR l, vecuu CR r, u64 mod, u32 ans_size = 0) NE {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  if (min(l.size(), r.size()) < CONV_NAIVE_MOD_THRESHOLD) return conv_naive_mod(l, r, mod, ans_size);
  CEXP u64 m0 = mint0::mod(), m1 = mint1::mod(), m2 = mint2::mod();
  const u64 r01 = mint1(m0).inv().val(), r02 = mint2(m0).inv().val(), r12 = mint2(m1).inv().val(),
            r02r12 = (u32)mul_mod_u(r02, r12, m2),
            w1 = m0 % mod, w2 = mul_mod_u(m0, m1, mod);
  const vec<mint0> d0 = conv_dft_um<ntt<mint0>, mint0>(ntt0, l, r, ans_size);
  const vec<mint1> d1 = conv_dft_um<ntt<mint1>, mint1>(ntt1, l, r, ans_size);
  const vec<mint2> d2 = conv_dft_um<ntt<mint2>, mint2>(ntt2, l, r, ans_size);
  vecuu ret(ans_size);
  flt_ (u32, i, 0, ans_size) {
    const u64 n1 = d1[i].val(), n2 = d2[i].val(), a = d0[i].val(),
              b = mul_mod_u((n1 + m1 - a), r01, m1),
              c = mul_mod_u(n2 + m2 - a, r02r12, m2) + mul_mod_u(m2 - b, r12, m2);
    ret[i] = (a + mul_mod_u(b, w1, mod) + mul_mod_u(c % m2, w2, mod)) % mod;
  }
  return ret;
}
template <class mint, class mint0, class mint1, class mint2>
CEXP vec<mint> conv_3ntt(ntt<mint0> &ntt0, ntt<mint1> &ntt1, ntt<mint2> &ntt2, vec<mint> CR l, vec<mint> CR r, u32 ans_size = 0) NE {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  if (min(l.size(), r.size()) < CONV_NAIVE_THRESHOLD) return conv_naive(l, r, ans_size);
  vecuu l_(l.size()), r_(r.size());
  flt_ (u32, i, 0, (u32)l.size()) l_[i] = l[i].val();
  flt_ (u32, i, 0, (u32)r.size()) r_[i] = r[i].val();
  vecuu _ = conv_3ntt_u64(ntt0, ntt1, ntt2, l_, r_, mint::mod(), ans_size);
  vec<mint> res(_.size());
  flt_ (u32, i, 0, (u32)_.size()) res[i] = _[i];
  return res;
}

}  // namespace tifa_libs::math

#endif