#ifndef TIFALIBS_CONV_FFT
#define TIFALIBS_CONV_FFT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <std::floating_point FP>
struct FFT {
  using C = std::complex<FP>;
  using data_t = C;

  explicit constexpr FFT() : rev(), w() {}

  constexpr u32 size() const { return (u32)rev.size(); }
  constexpr void bzr(u32 len) {
    u32 n = std::max<u32>(std::bit_ceil(len), 2);
    if (n == size()) return;
    rev.resize(n, 0);
    u32 k = (u32)(std::bit_width(n) - 1);
    for (u32 i = 0; i < n; ++i) rev[i] = (rev[i / 2] / 2) | ((i & 1) << (k - 1));
    w.resize(n);
    w[0].real(1);
    for (u32 i = 1; i < n; ++i) w[i] = {std::cos(TAU * (FP)i / (FP)n), std::sin(TAU * (FP)i / (FP)n)};
  }

  constexpr void dif(vec<C> &f, u32 n = 0) const {
    if (!n) n = size();
    if (f.size() < n) f.resize(n);
    assert(n <= size());
    for (u32 i = 0; i < n; ++i)
      if (i < rev[i]) std::swap(f[rev[i]], f[i]);
#pragma GCC diagnostic ignored "-Wsign-conversion"
    for (u32 i = 2, d = n / 2; i <= n; i *= 2, d /= 2)
      for (u32 j = 0; j < n; j += i) {
        auto l = f.begin() + j, r = f.begin() + j + i / 2;
        auto p = w.begin();
        for (u32 k = 0; k < i / 2; ++k, ++l, ++r, p += d) {
          C tmp = *r * *p;
          *r = *l - tmp;
          *l = *l + tmp;
        }
      }
#pragma GCC diagnostic warning "-Wsign-conversion"
  }
  constexpr void dit(vec<C> &f, u32 n = 0) const {
    if (!n) n = size();
    dif(f, n);
    for (u32 i = 0; i < n; ++i) f[i] /= (FP)n;
  }

 private:
  const FP TAU = std::acos((FP)-1.) * 2;

  vec<u32> rev;
  vec<C> w;
};

}  // namespace tifa_libs::math

#endif