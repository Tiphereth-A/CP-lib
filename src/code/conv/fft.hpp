#ifndef TIFALIBS_CONV_FFT
#define TIFALIBS_CONV_FFT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <std::floating_point FP>
struct FFT {
  using C = std::complex<FP>;
  using data_t = C;

  CEXPE FFT() NE : rev(), w() {}

  CEXP u32 size() CNE { return (u32)rev.size(); }
  CEXP void bzr(u32 len) NE {
    const u32 n = max<u32>(std::bit_ceil(len), 2);
    if (n == size()) return;
    rev.resize(n, 0);
    const u32 k = (u32)(std::bit_width(n) - 1);
    flt_ (u32, i, 0, n) rev[i] = (rev[i / 2] / 2) | ((i & 1) << (k - 1));
    w.resize(n), w[0].real(1);
    flt_ (u32, i, 1, n) w[i] = {std::cos(TAU * (FP)i / (FP)n), std::sin(TAU * (FP)i / (FP)n)};
  }
  CEXP void dif(vec<C> &f, u32 n = 0) CNE {
    if (!n) n = size();
    if (f.size() < n) f.resize(n);
    assert(n <= size());
    flt_ (u32, i, 0, n)
      if (i < rev[i]) swap(f[rev[i]], f[i]);
#pragma GCC diagnostic ignored "-Wsign-conversion"
    for (u32 i = 2, d = n / 2; i <= n; i *= 2, d /= 2)
      for (u32 j = 0; j < n; j += i) {
        auto l = f.begin() + j, r = f.begin() + j + i / 2;
        auto p = w.begin();
        for (u32 k = 0; k < i / 2; ++k, ++l, ++r, p += d) {
          const C _ = *r * *p;
          *r = *l - _, *l = *l + _;
        }
      }
#pragma GCC diagnostic warning "-Wsign-conversion"
  }
  CEXP void dit(vec<C> &f, u32 n = 0) CNE {
    if (!n) n = size();
    dif(f, n);
    flt_ (u32, i, 0, n) f[i] /= (FP)n;
  }

 private:
  const FP TAU = std::acos((FP)-1.) * 2;

  vecu rev;
  vec<C> w;
};

}  // namespace tifa_libs::math

#endif