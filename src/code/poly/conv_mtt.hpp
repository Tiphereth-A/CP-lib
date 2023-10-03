#ifndef TIFALIBS_POLY_CONV_MTT
#define TIFALIBS_POLY_CONV_MTT

#include "../util/util.hpp"

#include "fft.hpp"

namespace tifa_libs::math {

template <class mint, class FP = double>
inline vec<mint> conv_mtt(vec<mint> const &l, vec<mint> const &r, size_t ans_size) {
  using C = typename FFT<FP>::C;
  static FFT<FP> fft;
  fft.bzr(std::min(l.size() + r.size() - 1, ans_size));
  size_t n = fft.size();
  constexpr int OFS = ((int)sizeof(decltype(mint::mod())) * 8 - bit::cntl0(mint::mod() - 1) + 1) / 2;
  constexpr u32 MSK = ((1u << OFS) - 1);
  vec<mint> ans(ans_size);
  vec<C> a(n), b(n);
  for (size_t i = 0; i < l.size(); ++i) a[i] = {(FP)(l[i].val() & MSK), (FP)(l[i].val() >> OFS)};
  for (size_t i = 0; i < r.size(); ++i) b[i] = {(FP)(r[i].val() & MSK), (FP)(r[i].val() >> OFS)};
  fft.dif(a);
  fft.dif(b);
  {
    vec<C> p(n), q(n);
    for (size_t i = 0, j; i < n; ++i) {
      j = (n - i) & (n - 1);
      C da = (a[i] + std::conj(a[j])) * C(.5, 0), db = (a[i] - std::conj(a[j])) * C(0, -.5), dc = (b[i] + std::conj(b[j])) * C(.5, 0), dd = (b[i] - std::conj(b[j])) * C(.5, .5);
      p[j] = da * dc + da * dd;
      q[j] = db * dc + db * dd;
    }
    a = p;
    b = q;
  }
  fft.dit(a);
  fft.dit(b);
  for (size_t i = 0; i < ans_size; ++i) ans[i] = (u64)(a[i].real() + .5) + ((u64)((a[i].imag() + b[i].real()) + .5) << OFS) + ((u64)(b[i].imag() + .5) << (OFS * 2));
  return ans;
}
template <class mint, class FP = double>
inline vec<mint> conv_mtt(vec<mint> const &l, vec<mint> const &r) { return conv_mtt<mint, FP>(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif