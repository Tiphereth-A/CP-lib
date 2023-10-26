#ifndef TIFALIBS_CONV_NTT
#define TIFALIBS_CONV_NTT

#include "../bit/bceil.hpp"
#include "../math/proot_u64.hpp"
#include "../math/qpow.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint>
struct NTT {
  static_assert((mint::mod() & 3) == 1, "MOD must be prime with 4k+1");

  NTT() : root() {}

  usz size() const { return root.size(); }
  void bzr(usz len) {
    usz n = bit::bceil(len);
    assert((mint::mod() - 1) % n == 0);
    if (n == size()) return;
    root.resize(n);
    root[0] = 1;
    mint w = qpow(G, (mint::mod() - 1) / n);
    for (usz i = 1; i < n; ++i) root[i] = root[i - 1] * w;
  }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
  void dif(vec<mint> &f) const {
    usz n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (usz i = n / 2, d = 1; i; i /= 2, d *= 2)
      for (usz j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint u, t;
        for (usz k = 0; k < i; ++k, w += d) {
          f[j | k] = (u = f[j | k]) + (t = f[i | j | k]);
          f[i | j | k] = (u - t) * (*w);
        }
      }
  }
  void dit(vec<mint> &f) const {
    usz n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (usz i = 1, d = n / 2; d; i *= 2, d /= 2)
      for (usz j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint t;
        for (usz k = 0; k < i; ++k, w += d) {
          f[i | j | k] = f[j | k] - (t = f[i | j | k] * (*w));
          f[j | k] += t;
        }
      }
    std::reverse(f.begin() + 1, f.end());
    mint t = mint(n).inv();
    for (usz i = 0; i < n; ++i) f[i] *= t;
  }
#pragma GCC diagnostic pop

 private:
  const mint G = proot_u64(mint::mod());
  vec<mint> root;
};

}  // namespace tifa_libs::math

#endif