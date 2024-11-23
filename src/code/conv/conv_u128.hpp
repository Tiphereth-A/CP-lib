#ifndef TIFALIBS_CONV_CONV_U128
#define TIFALIBS_CONV_CONV_U128

#include "../math/mint.hpp"
#include "../math/mint_s30.hpp"
#include "conv_dft.hpp"
#include "conv_naive.hpp"
#include "ntt.hpp"

namespace tifa_libs::math {

// max = 167772161 * 469762049 * 754974721 \approx 5.95e25
template <class T>
vec<u128> conv_u128(vec<T> CR l, vec<T> CR r, u32 ans_size = 0) {
  static CEXP u32 m0 = 167772161, m1 = 469762049, m2 = 754974721;
  using mint0 = mint<mint_s30, m0>;
  using mint1 = mint<mint_s30, m1>;
  using mint2 = mint<mint_s30, m2>;
  static CEXP u32 r01 = inverse(m0, mint1::mod()), r02 = inverse(m0, mint2::mod()), r12 = inverse(m1, mint2::mod()), r02r12 = (u64)r02 * r12 % m2;
  static CEXP u64 w1 = m0, w2 = (u64)m0 * m1;
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  if (l.empty() && r.empty()) return {};
  if (min(l.size(), r.size()) < 128) return conv_naive<T, u128>(l, r, ans_size);
  static NTT<mint0> ntt0;
  static NTT<mint1> ntt1;
  static NTT<mint2> ntt2;
  const vec<mint0> d0 = conv_dft_um<NTT<mint0>, mint0>(ntt0, l, r, ans_size);
  const vec<mint1> d1 = conv_dft_um<NTT<mint1>, mint1>(ntt1, l, r, ans_size);
  const vec<mint2> d2 = conv_dft_um<NTT<mint2>, mint2>(ntt2, l, r, ans_size);
  vec<u128> ret(ans_size);
  flt_ (u32, i, 0, ans_size) {
    const u64 n1 = d1[i].val(), n2 = d2[i].val(), a = d0[i].val(), b = (n1 + m1 - a) * r01 % m1;
    const u128 c = ((n2 + m2 - a) * r02r12 + (m2 - b) * r12) % m2;
    ret[i] = a + b * w1 + c * w2;
  }
  return ret;
}

}  // namespace tifa_libs::math

#endif