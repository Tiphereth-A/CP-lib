#ifndef TIFALIBS_CONV_CONV_NTT_LARGE
#define TIFALIBS_CONV_CONV_NTT_LARGE

#include "conv_dft.hpp"

namespace tifa_libs::math {

template <class NTT_t, class mint>
constexpr vec<mint> conv_ntt_large(NTT_t &ntt, vec<mint> l, vec<mint> r, u32 ans_size = 0) {
  const u32 n = (u32)l.size(), m = (u32)r.size();
  if (!ans_size) ans_size = n + m - 1;
  if (ans_size <= NTT_t::max_size) return conv_dft<NTT_t, mint>(ntt, l, r, ans_size);
  constexpr u32 ms = NTT_t::max_size, hms = ms / 2, ims = mint(ms).inv().data();
  const u32 dn = (n + hms - 1) / hms, dm = (m + hms - 1) / hms;

  ntt.bzr(std::max(dn, dm));
  vvec<mint> as(dn), bs(dm), cs(dn + dm - 1, vec<mint>(ms));
  for (u32 i = 0; i < dn; ++i) {
    const u32 ofs = hms * i;
    (as[i] = vec<mint>(l.begin() + ofs, l.begin() + std::min(n, ofs + hms))).resize(ms);
    ntt.dif(as[i]);
  }
  for (u32 j = 0; j < dm; ++j) {
    const u32 ofs = hms * j;
    (bs[j] = vec<mint>(r.begin() + ofs, r.begin() + std::min(m, ofs + hms))).resize(ms);
    ntt.dif(bs[j]);
  }
  for (u32 i = 0; i < dn; ++i)
    for (u32 j = 0; j < dm; ++j)
      for (u32 k = 0; k < ms; ++k) cs[i + j][k] += as[i][k] * bs[j][k];
  vec<mint> res(n + m - 1);
  for (u32 i = 0; i < dn + dm - 1; ++i) {
    ntt.dit(cs[i]);
    const u32 ofs = hms * i, jmax = std::min(n + m - 1 - ofs, ms);
    for (u32 j = 0; j < jmax; ++j) res[ofs + j] += cs[i][j] * ims;
  }
  return res;
}
template <class NTT_t, class mint, class T = u64>
constexpr vec<mint> conv_ntt_large_u64(NTT_t &ntt, vec<T> const &l, vec<T> const &r, u32 ans_size = 0) {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  vec<mint> l_, r_;
  l_.reserve(l.size());
  r_.reserve(r.size());
  for (auto i : l) l_.push_back(i);
  for (auto i : r) r_.push_back(i);
  return conv_ntt_large(ntt, l_, r_, ans_size);
}

}  // namespace tifa_libs::math

#endif