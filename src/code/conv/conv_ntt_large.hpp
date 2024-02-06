#ifndef TIFALIBS_CONV_CONV_NTT_LARGE
#define TIFALIBS_CONV_CONV_NTT_LARGE

#include "conv_dft.hpp"

namespace tifa_libs::math {

template <class NTT_t, class mint>
constexpr vec<mint> conv_ntt_large(NTT_t &ntt, vec<mint> l, vec<mint> r, u32 ans_size = 0) {
  const u32 n = (u32)l.size(), m = (u32)r.size();
  constexpr u32 len = NTT_t::max_size;
  if (n + m - 1 <= len) return conv_dft<NTT_t, mint>(ntt, l, r, ans_size);
  if (!ans_size) ans_size = n + m - 1;

  ntt.bzr(len);
  vvec<mint> as, bs;
  for (u32 i = 0; i < l.size(); i += len / 2) {
    vec<mint> v{l.begin() + i, l.begin() + std::min(i + len / 2, (u32)l.size())};
    ntt.dif(v);
    as.push_back(v);
  }
  for (u32 i = 0; i < r.size(); i += len / 2) {
    vec<mint> v{r.begin() + i, r.begin() + std::min(i + len / 2, (u32)r.size())};
    ntt.dif(v);
    bs.push_back(v);
  }
  vvec<mint> cs(as.size() + bs.size() - 1, vec<mint>(len));
  for (u32 i = 0; i < as.size(); ++i)
    for (u32 j = 0; j < bs.size(); ++j)
      for (u32 k = 0; k < len; ++k) cs[i + j][k] += as[i][k] * bs[j][k];
  for (auto &v : cs) ntt.dit(v);
  vec<mint> c(l.size() + r.size() - 1);
  for (u32 i = 0; i < cs.size(); ++i) {
    u32 ofs = len / 2 * i;
    for (u32 j = 0, je = std::min(len, (u32)c.size() - ofs); j < je; ++j) c[j + ofs] += cs[i][j];
  }
  c.resize(ans_size);
  return c;
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