#ifndef TIFALIBS_POLY_FFT
#define TIFALIBS_POLY_FFT

#include "../bit/bceil.hpp"
#include "../bit/log2.hpp"

namespace tifa_libs::math {

template <class FP>
struct FFT {
  static_assert(std::is_floating_point_v<FP>);
  using C = std::complex<FP>;

  constexpr FFT() : rev(), w() {}

  size_t size() const { return rev.size(); }
  void bzr(size_t len) {
    size_t n = bit::bceil(len);
    int k = bit::log2(n);
    if (n == size()) return;
    rev.resize(n, 0);
    for (size_t i = 0; i < n; ++i) rev[i] = (rev[i / 2] / 2) | ((i & 1) << (k - 1));
    w.resize(n);
    w[0].real(1);
    for (size_t i = 1; i < n; ++i) w[i] = {std::cos(TAU * (FP)i / (FP)n), std::sin(TAU * (FP)i / (FP)n)};
  }

  void dif(vec<C> &f) const {
    size_t n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (size_t i = 0; i < n; ++i)
      if (i < rev[i]) std::swap(f[rev[i]], f[i]);
    for (size_t i = 2, d = n / 2; i <= n; i *= 2, d /= 2)
      for (size_t j = 0; j < n; j += i) {
        auto l = f.begin() + j, r = f.begin() + j + i / 2;
        auto p = w.begin();
        for (size_t k = 0; k < i / 2; ++k, ++l, ++r, p += d) {
          C tmp = *r * *p;
          *r = *l - tmp;
          *l = *l + tmp;
        }
      }
  }
  void dit(vec<C> &f) const {
    size_t n = size();
    dif(f);
    for (size_t i = 0; i < n; ++i) f[i] /= (FP)n;
  }

 private:
  const FP TAU = std::acos((FP)-1.) * 2;

  vec<size_t> rev;
  vec<C> w;
};

}  // namespace tifa_libs::math

#endif