#ifndef TIFALIBS_CONV_NTT32
#define TIFALIBS_CONV_NTT32

#include "../bit/bceil.hpp"
#include "../bit/ispow2.hpp"
#include "../math/proot_u32.hpp"
#include "../math/qpow.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint>
struct NTT32 {
  static_assert(sizeof(mint::mod()) <= 4 && (mint::mod() & 3) == 1, "MOD must be prime with 4k+1");

  static constexpr mint G = proot_u32(mint::mod());

  NTT32() : root() {}

  u32 size() const { return (u32)root.size(); }
  void bzr(u32 len) {
    u32 n = bit::bceil(len);
    assert((mint::mod() - 1) % n == 0);
    if (n == size()) return;
    root.resize(n);
    root[0] = 1;
    mint w = qpow(G, (mint::mod() - 1) / n);
    for (u32 i = 1; i < n; ++i) root[i] = root[i - 1] * w;
  }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
  void dif(vec<mint> &f, u32 n = 0) const {
    if (!n) n = (u32)f.size();
    else if (f.size() < n) f.resize(n);
    assert(bit::ispow2(n) && n <= size() * 2);
    for (u32 i = n / 2, d = 1; i; i /= 2, d *= 2)
      for (u32 j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint u, t;
        for (u32 k = 0; k < i; ++k, w += d) {
          f[j | k] = (u = f[j | k]) + (t = f[i | j | k]);
          f[i | j | k] = (u - t) * (*w);
        }
      }
  }
  void dit(vec<mint> &f, u32 n = 0) const {
    if (!n) n = (u32)f.size();
    else if (f.size() < n) f.resize(n);
    assert(bit::ispow2(n) && n <= size() * 2);
    for (u32 i = 1, d = n / 2; d; i *= 2, d /= 2)
      for (u32 j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint t;
        for (u32 k = 0; k < i; ++k, w += d) {
          f[i | j | k] = f[j | k] - (t = f[i | j | k] * (*w));
          f[j | k] += t;
        }
      }
    std::reverse(f.begin() + 1, f.end());
    mint t = mint(n).inv();
    for (u32 i = 0; i < n; ++i) f[i] *= t;
  }
#pragma GCC diagnostic pop

 private:
  vec<mint> root;
};

}  // namespace tifa_libs::math

#endif