#ifndef TIFALIBS_CONV_CONV_U128
#define TIFALIBS_CONV_CONV_U128

#include "../math/mint_s30.hpp"
#include "../util/util.hpp"
#include "conv_dft.hpp"
#include "conv_naive.hpp"
#include "ntt32.hpp"

namespace tifa_libs::math {

// max = 167772161 * 469762049 * 754974721 \approx 5.95e25
template <class T>
vec<u128> conv_u128(vec<T> const &l, vec<T> const &r, u32 ans_size = 0) {
  static constexpr u32 m0 = 167772161, m1 = 469762049, m2 = 754974721;
  using mint0 = mint_s30<m0>;
  using mint1 = mint_s30<m1>;
  using mint2 = mint_s30<m2>;
  static constexpr u32 r01 = mint1(m0).inv().val(), r02 = mint2(m0).inv().val(), r12 = mint2(m1).inv().val(), r02r12 = (u64)r02 * r12 % m2;
  static constexpr u64 w1 = m0, w2 = (u64)m0 * m1;

  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  if (l.empty() && r.empty()) return {};
  if (std::min(l.size(), r.size()) < 128) return conv_naive<T, u128>(l, r, ans_size);

  static NTT32<mint0> ntt0;
  static NTT32<mint1> ntt1;
  static NTT32<mint2> ntt2;

  vec<mint0> d0 = conv_dft_u64<NTT32<mint0>, mint0>(ntt0, l, r, ans_size);
  vec<mint1> d1 = conv_dft_u64<NTT32<mint1>, mint1>(ntt1, l, r, ans_size);
  vec<mint2> d2 = conv_dft_u64<NTT32<mint2>, mint2>(ntt2, l, r, ans_size);

  vec<u128> ret(ans_size);
  for (u32 i = 0; i < ans_size; ++i) {
    u64 n1 = d1[i].val(), n2 = d2[i].val(), a = d0[i].val(), b = (n1 + m1 - a) * r01 % m1;
    u128 c = ((n2 + m2 - a) * r02r12 + (m2 - b) * r12) % m2;
    ret[i] = a + b * w1 + c * w2;
  }
  return ret;
}

}  // namespace tifa_libs::math

#endif