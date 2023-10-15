#ifndef TIFALIBS_CONV_NTT
#define TIFALIBS_CONV_NTT

#include "../bit/bceil.hpp"
#include "../math/proot_u64.hpp"
#include "../math/qpow.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint>
struct NTT {
  static constexpr u64 MOD = mint::mod();
  static_assert((MOD & 3) == 1, "MOD must be prime with 4k+1");

  NTT() : root() {}

  size_t size() const { return root.size(); }
  void bzr(size_t len) {
    size_t n = bit::bceil(len);
    assert((MOD - 1) % n == 0);
    if (n == size()) return;
    root.resize(n);
    root[0] = 1;
    mint w = qpow(G, (MOD - 1) / n);
    for (size_t i = 1; i < n; ++i) root[i] = root[i - 1] * w;
  }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
  void dif(vec<mint> &f) const {
    size_t n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (size_t i = n / 2, d = 1; i; i /= 2, d *= 2)
      for (size_t j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint u, t;
        for (size_t k = 0; k < i; ++k, w += d) {
          f[j | k] = (u = f[j | k]) + (t = f[i | j | k]);
          f[i | j | k] = (u - t) * (*w);
        }
      }
  }
  void dit(vec<mint> &f) const {
    size_t n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (size_t i = 1, d = n / 2; d; i *= 2, d /= 2)
      for (size_t j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint t;
        for (size_t k = 0; k < i; ++k, w += d) {
          f[i | j | k] = f[j | k] - (t = f[i | j | k] * (*w));
          f[j | k] += t;
        }
      }
    std::reverse(f.begin() + 1, f.end());
    mint t = mint(n).inv();
    for (size_t i = 0; i < n; ++i) f[i] *= t;
  }
#pragma GCC diagnostic pop

 private:
  const mint G = proot_u64(MOD);

  vec<mint> root;
};

}  // namespace tifa_libs::math

#endif