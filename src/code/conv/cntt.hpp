#ifndef TIFALIBS_CONV_CNTT
#define TIFALIBS_CONV_CNTT

#include "../bit/bceil.hpp"
#include "../bit/log2.hpp"
#include "../math/qpow.hpp"

namespace tifa_libs::math {

namespace CNTT_impl_ {

template <class mint>
constexpr std::complex<mint> omega(u32 mod) {
  if (mod == 65537) return {4, 17573};
  if (mod == 998244353) return {1, 1};
  if (mod == 999292927) return {1, 8};
}

}  // namespace CNTT_impl_

template <class mint>
struct CNTT {
  using Zpi = std::complex<mint>;
  static constexpr u32 MOD = mint::mod();

  CNTT() : rev() {}

  usz size() const { return rev.size(); }
  void bzr(usz len) {
    usz n = bit::bceil(len);
    if (n == size()) return;
    rev.resize(n, 0);
    int k = bit::log2(n);
    for (usz i = 0; i < n; ++i) rev[i] = (rev[i / 2] / 2) | ((i & 1) << (k - 1));
  }

  void dif(vec<Zpi> &f) const { difdit(f); }
  void dit(vec<Zpi> &f) const { difdit<true>(f); }

 private:
  vec<u32> rev;
  const Zpi W = CNTT_impl_::omega<mint>(MOD);

  template <bool inv = false>
  void difdit(vec<Zpi> &f) const {
    usz n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (usz i = 0; i < n; ++i)
      if (i < rev[i]) std::swap(f[rev[i]], f[i]);
    for (u32 mid = 1; mid < n; mid <<= 1) {
      Zpi Wn = qpow(W, ((((MOD + 1) & 3) ? (u64)MOD : (u64)MOD * MOD) - 1) / 2 / mid);
      if constexpr (inv) Wn = qpow(Wn, (((MOD + 1) & 3) ? (u64)MOD : (u64)MOD * MOD) - 2);
      for (u32 r = mid << 1, j = 0; j < n; j += r) {
        Zpi w{1};
        for (u32 k = 0; k < mid; k++, w *= Wn) {
          Zpi x = f[j + k], y = w * f[j + mid + k];
          f[j + k] = x + y;
          f[j + mid + k] = x - y;
        }
      }
    }
  }
};

}  // namespace tifa_libs::math

#endif