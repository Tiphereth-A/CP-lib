#ifndef TIFALIBS_POLY_CONV_MTT
#define TIFALIBS_POLY_CONV_MTT

#include "../util/util.hpp"

#include "../bit/bceil.hpp"
#include "fft.hpp"

namespace tifa_libs::math {

template <class mint, class DBL = double>
inline vec<mint> conv_mtt(vec<mint> l, vec<mint> const &r, size_t ans_size) {
  static FFT<DBL> fft;
  using C = typename FFT<DBL>::comp;
  vec<C> a, b;
  a.reserve(l.size());
  b.reserve(r.size());
  for (size_t i = 0; i < l.size(); ++i) a.emplace_back(l[i].val() & 0x7fff, l[i].val() >> 15);
  for (size_t i = 0; i < r.size(); ++i) b.emplace_back(r[i].val() & 0x7fff, r[i].val() >> 15);
  l.resize(ans_size);
  size_t n = bit::bceil(ans_size);
  a.resize(n);
  b.resize(n);
  fft(a);
  fft(b);
  vec<C> p(n), q(n);
  for (size_t i = 0; i < n; ++i) p[i] = b[i] * (a[i] + conj(a[(n - i) % n])) * C{.5, 0};
  for (size_t i = 0; i < n; ++i) q[i] = b[i] * (a[i] - conj(a[(n - i) % n])) * C{0, -.5};
  fft(p, true);
  fft(q, true);
  for (size_t i = 0; i < ans_size; ++i) l[i] = (u64)(p[i].real() / (DBL)n + .5) % mint::mod() + (((u64)((p[i].imag() + q[i].real()) / (DBL)n + .5) % mint::mod()) << 15) + (((u64)(q[i].imag() / (DBL)n + .5) % mint::mod()) << 30);
  return l;
}
template <class mint>
inline vec<mint> conv_mtt(vec<mint> l, vec<mint> r) { return conv_mtt(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif