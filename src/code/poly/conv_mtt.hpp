#ifndef TIFALIBS_POLY_CONV_MTT
#define TIFALIBS_POLY_CONV_MTT

#include "../util/util.hpp"

#include "../bit/bceil.hpp"
#include "fft.hpp"

namespace tifa_libs::math {

template <class mint, class DBL = double>
inline vec<mint> conv_mtt(vec<mint> l, vec<mint> const &r, size_t ans_size) {
  static FFT<DBL> fft;
  using C = typename FFT<DBL>::C;
  vec<C> a(l.size()), b(r.size());
  for (size_t i = 0; i < l.size(); ++i) a[i].real((DBL)(l[i].val() & 0x7fff)), a[i].imag((DBL)(l[i].val() >> 15));
  for (size_t i = 0; i < r.size(); ++i) b[i].real((DBL)(r[i].val() & 0x7fff)), b[i].imag((DBL)(r[i].val() >> 15));
  l.resize(ans_size);
  size_t n = bit::bceil(std::min(l.size() + r.size() - 1, ans_size));
  a.resize(n);
  b.resize(n);
  fft.run(a);
  fft.run(b);
  vec<C> p(n), q(n);
  for (size_t i = 0; i < n; ++i) p[i] = b[i] * (a[i] + conj(a[i ? n - i : 0])) * C{.5, 0};
  for (size_t i = 0; i < n; ++i) q[i] = b[i] * (a[i] - conj(a[i ? n - i : 0])) * C{0, -.5};
  fft.template run<true>(p);
  fft.template run<true>(q);
  for (size_t i = 0; i < l.size(); ++i) l[i] = ((u64)(p[i].real() / (DBL)n + .5) + (((u64)((p[i].imag() + q[i].real()) / (DBL)n + .5)) << 15) + (((u64)(q[i].imag() / (DBL)n + .5)) << 30)) % mint::mod();
  return l;
}
template <class mint>
inline vec<mint> conv_mtt(vec<mint> const &l, vec<mint> const &r) { return conv_mtt(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif