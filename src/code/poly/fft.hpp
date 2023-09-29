#ifndef TIFALIBS_POLY_FFT
#define TIFALIBS_POLY_FFT

#include "../util/util.hpp"

#include "fft_info.hpp"

namespace tifa_libs::math {

template <class FP>
struct FFT {
  static_assert(std::is_floating_point_v<FP>);

  using comp = std::complex<FP>;

  constexpr FFT() = default;
  template <bool inv = false>
  constexpr void operator()(vec<comp> &g) {
    size_t n = g.size();
    FFT_INFO::init(n);
    w.resize(n);
    w[0] = 1;
    for (size_t i = 1; i < n; ++i)
      if constexpr (inv) w[i] = {std::cos(TAU * (FP)i / (FP)n), -std::sin(TAU * (FP)i / (FP)n)};
      else w[i] = {std::cos(TAU * (FP)i / (FP)n), std::sin(TAU * (FP)i / (FP)n)};
    for (size_t i = 0; i < n; ++i)
      if (i < FFT_INFO::root[i]) std::swap(g[i], g[FFT_INFO::root[i]]);
    for (size_t i = 2; i <= n; i <<= 1) {
      for (size_t j = 1; j < i / 2; ++j)
        if constexpr (inv) w[j] = {std::cos(TAU / (FP)i * (FP)j), -std::sin(TAU / (FP)i * (FP)j)};
        else w[j] = {std::cos(TAU / (FP)i * (FP)j), std::sin(TAU / (FP)i * (FP)j)};
      for (size_t j = 0; j < n; j += i) {
        auto f = g.begin() + j, h = g.begin() + j + i / 2;
        for (size_t k = 0; k < i / 2; ++k) {
          comp p = f[k], q = h[k] * w[k];
          f[k] = p + q;
          h[k] = p - q;
        }
      }
    }
  }

private:
  constexpr static FP TAU = FP(std::acos((FP)1) * 2);

  static inline vec<comp> w;
};

}  // namespace tifa_libs::math

#endif