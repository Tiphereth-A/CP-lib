#ifndef TIFALIBS_CONV_FFT_R3
#define TIFALIBS_CONV_FFT_R3

#include "../math/eint.hpp"

namespace tifa_libs::math {

template <class T>
class fft_r3 {
  using EI = eint<T>;
  u32 s = 1;
  vec<EI> tmp;

 public:
  using data_t = eint<T>;

  CEXP u32 size() CNE { return s; }
  CEXP void bzr(u32 len) NE {
    for (; 2 * s < len; s *= 3);
    tmp.resize(s * 3);
  }

  // Calculate the product of polynomial {@code f} and $x^t$ in $T[x]/(x^m - \omega)$
  // result is in {@code to}
  CEXP void twiddle(data_t *p, u32 m, u32 t, data_t *to) CNE {
    assert(t <= 3 * m);
    if (!t || t == 3 * m) {
      copy_n(p, m, to);
      return;
    }
    u32 n;
    data_t _0, _1;
    if (t < m) n = t, _0 = 1, _1 = EI::w;
    else if (t < 2 * m) n = t - m, _0 = EI::w, _1 = EI::w2;
    else n = t - 2 * m, _0 = EI::w2, _1 = 1;
    flt_ (u32, j, 0, n) to[j] = p[m - n + j] * _1;
    flt_ (u32, j, n, m) to[j] = p[j - n] * _0;
  }
  // @param p A polynomial from $(T[x]/(x^m - \omega))[y]/(y^r - 1)$
  // result: Fourier transform (w.r.t. y) in 3-reversed order, inplace.
  CEXP void dif(data_t *p, u32 m, u32 r) NE {
    for (u32 rr = r / 3; rr >= 1; rr /= 3)
      for (u32 k = 0; k < r; k += rr * 3)
        flt_ (u32, i, k, k + rr) {
          flt_ (u32, j, 0, m) {
            tmp[j] = p[i * m + j] + p[(i + rr) * m + j] + p[(i + 2 * rr) * m + j];
            tmp[m + j] = p[i * m + j] + EI::w * p[(i + rr) * m + j] + EI::w2 * p[(i + 2 * rr) * m + j];
            tmp[2 * m + j] = p[i * m + j] + EI::w2 * p[(i + rr) * m + j] + EI::w * p[(i + 2 * rr) * m + j];
            p[i * m + j] = tmp[j];
          }
          twiddle(tmp.data() + m, m, 3 * (i - k) * m / (rr * 3), p + m * rr + i * m);
          twiddle(tmp.data() + 2 * m, m, 6 * (i - k) * m / (rr * 3), p + 2 * m * rr + i * m);
        }
  }
  // @param p A polynomial in $(T[x]/(x^m - \omega))[y]/(y^r - 1)$ with coefficients in 3-reversed order.
  // result: inverse Fourier transform in normal order, inplace.
  CEXP void dit(data_t *p, u32 m, u32 r) NE {
    for (u32 rr = 1; rr < r; rr *= 3)
      for (u32 k = 0; k < r; k += rr * 3)
        flt_ (u32, i, k, k + rr) {
          twiddle(p + m * rr + i * m, m, 3 * m - 3 * (i - k) * m / (rr * 3), tmp.data() + m);
          twiddle(p + 2 * m * rr + i * m, m, 3 * m - 6 * (i - k) * m / (rr * 3), tmp.data() + 2 * m);
          flt_ (u32, j, 0, m) {
            tmp[j] = p[i * m + j];
            p[i * m + j] = tmp[j] + tmp[m + j] + tmp[2 * m + j];
            p[(i + rr) * m + j] = tmp[j] + EI::w2 * tmp[m + j] + EI::w * tmp[2 * m + j];
            p[(i + 2 * rr) * m + j] = tmp[j] + EI::w * tmp[m + j] + EI::w2 * tmp[2 * m + j];
          }
        }
  }
};

}  // namespace tifa_libs::math

#endif