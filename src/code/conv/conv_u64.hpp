#ifndef TIFALIBS_CONV_CONV_u64
#define TIFALIBS_CONV_CONV_u64

#include "conv_naive.hpp"
#include "fft_r3.hpp"

namespace tifa_libs::math {

template <class T>
vecuu conv_u64(vec<T> CR a, vec<T> CR b, u32 ans_size = 0) NE {
  const u32 n = (u32)a.size(), m = (u32)b.size();
  if (!ans_size) ans_size = n + m - 1;
  if (a.empty() && b.empty()) return {};
  if (min(n, m) < CONV_NAIVE_THRESHOLD) return conv_naive<T, u64>(a, b, ans_size);
  static FFT_R3<T> fft;
  using EI = FFT_R3<T>::data_t;
  CEXP static EI inv_3{-T(1) / 3 * 2 + 1, 0};
  fft.bzr(n + m - 1);
  u32 s = fft.size();
  vec<EI> pa(s), pb(s);
  for (u32 i = 0; i < min(s, n); ++i) pa[i].real(a[i]);
  for (u32 i = s; i < min(2 * s, n); ++i) pa[i - s].imag(a[i]);
  for (u32 i = 0; i < min(s, m); ++i) pb[i].real(b[i]);
  for (u32 i = s; i < min(2 * s, m); ++i) pb[i - s].imag(b[i]);
  vec<EI> pc(4 * s);
  auto mul = [](auto&& mul, EI* p, EI* q, EI* to, u32 n) {
    if (n <= 27) {
      fill_n(to, n, 0);
      flt_ (u32, i, 0, n) {
        flt_ (u32, j, 0, n - i) to[i + j] += p[i] * q[j];
        flt_ (u32, j, n - i, n) to[i + j - n] += p[i] * q[j] * EI::w;
      }
      return;
    }
    u32 m = 1;
    for (; m * m < n; m *= 3);
    u32 r = n / m;
    EI inv{1};
    for (u32 i = 1; i < r; i *= 3) inv *= inv_3;
    flt_ (u32, i, 0, r) {
      fft.twiddle(p + m * i, m, m / r * i, to + m * i);
      fft.twiddle(q + m * i, m, m / r * i, to + n + m * i);
    }
    fft.dif(to, m, r), fft.dif(to + n, m, r);
    flt_ (u32, i, 0, r) mul(mul, to + m * i, to + n + m * i, to + 2 * n + m * i, m);
    fft.dit(to + 2 * n, m, r);
    flt_ (u32, i, 0, n) to[2 * n + i] *= inv;
    flt_ (u32, i, 0, r) fft.twiddle(to + 2 * n + m * i, m, 3 * m - m / r * i, to + n + m * i);
    flt_ (u32, i, 0, r) {
      flt_ (u32, j, 0, m) p[m * i + j] = conj(p[m * i + j]), q[m * i + j] = conj(q[m * i + j]);
      fft.twiddle(p + m * i, m, 2 * m / r * i, to + m * i);
      fft.twiddle(q + m * i, m, 2 * m / r * i, p + m * i);
    }
    fft.dif(to, m, r), fft.dif(p, m, r);
    flt_ (u32, i, 0, r) mul(mul, to + m * i, p + m * i, to + 2 * n + m * i, m);
    fft.dit(to + 2 * n, m, r);
    flt_ (u32, i, 0, n) to[2 * n + i] *= inv;
    flt_ (u32, i, 0, r) fft.twiddle(to + 2 * n + m * i, m, 3 * m - 2 * m / r * i, q + m * i);
    fill_n(to, n, 0);
    flt_ (u32, i, 0, n) {
      to[i] += (1 - EI::w) * to[n + i] + (1 - EI::w2) * conj(q[i]);
      if (i + m < n) to[i + m] += (EI::w2 - EI::w) * (to[n + i] - conj(q[i]));
      else to[i + m - n] += (1 - EI::w2) * (to[n + i] - conj(q[i]));
    }
    flt_ (u32, i, 0, n) to[i] *= inv_3;
  };
  mul(mul, pa.data(), pb.data(), pc.data(), s);
  vec<T> ans(ans_size);
  flt_ (u32, i, 0, min(s, ans_size)) ans[i] = pc[i].real();
  flt_ (u32, i, s, min(2 * s, ans_size)) ans[i] = pc[i - s].imag();
  return ans;
}

}  // namespace tifa_libs::math

#endif