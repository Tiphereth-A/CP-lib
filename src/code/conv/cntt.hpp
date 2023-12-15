#ifndef TIFALIBS_CONV_CNTT
#define TIFALIBS_CONV_CNTT

#include "../math/proot_gint.hpp"
#include "../math/qpow.hpp"

namespace tifa_libs::math {

template <class mint, i64 M = -1>
struct CNTT {
  using Zpi = GaussInt<mint, M>;

  CNTT() {}

  u32 size() const { return (u32)rev.size(); }
  void bzr(u32 len) {
    u32 n = std::max<u32>(std::bit_ceil(len), 2);
    if (n == size()) return;
    rev.resize(n, 0);
    u32 k = (u32)(std::bit_width(n) - 1);
    for (u32 i = 0; i < n; ++i) rev[i] = (rev[i / 2] / 2) | ((i & 1) << (k - 1));
    Wn.resize(k);
    IWn.resize(k);
    for (u32 i = 0, mid = 1; i < k; mid <<= 1, ++i) Wn[i] = qpow(W, ((((mint::mod() + 1) & 3) ? (u64)mint::mod() : (u64)mint::mod() * mint::mod()) - 1) / 2 / mid);
    for (u32 i = 0; i < k; ++i) IWn[i] = qpow(Wn[i], (((mint::mod() + 1) & 3) ? (u64)mint::mod() : (u64)mint::mod() * mint::mod()) - 2);
  }

  void dif(vec<Zpi> &f) const { difdit(f); }
  void dit(vec<Zpi> &f) const { difdit<true>(f); }

 private:
  vec<u32> rev;
  const Zpi W = proot_gint<mint>();
  vec<Zpi> Wn, IWn;

  template <bool inv = false>
  void difdit(vec<Zpi> &f) const {
    u32 n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (u32 i = 0; i < n; ++i)
      if (i < rev[i]) std::swap(f[rev[i]], f[i]);
    for (u32 mid = 1, k = 0; mid < n; mid <<= 1, ++k) {
      Zpi now;
      if constexpr (inv) now = IWn[k];
      else now = Wn[k];
      for (u32 r = mid << 1, j = 0; j < n; j += r) {
        Zpi w{1};
        for (u32 k = 0; k < mid; k++, w *= now) {
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