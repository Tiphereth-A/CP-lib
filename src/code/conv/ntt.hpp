#ifndef TIFALIBS_CONV_NTT
#define TIFALIBS_CONV_NTT

#include "../bit/lowbit.hpp"
#include "../math/qpow.hpp"
#include "../nt/proot.hpp"

namespace tifa_libs::math {

template <class mint>
struct NTT {
  using data_t = mint;

  static_assert(is_prime(mint::mod()) && (mint::mod() & 3) == 1, "MOD must be prime with 4k+1");
  static CEXP u64 max_size = bit::lowbit(mint::mod() - 1);

  const mint G = proot(mint::mod());

  explicit CEXP NTT() : root() {}

  CEXP u32 size() const { return (u32)root.size(); }
  CEXP void bzr(u32 len = max_size) {
    const u32 n = std::bit_ceil(len);
    assert(n <= max_size);
    if (n == size()) return;
    root.resize(n), root[0] = 1;
    const mint w = qpow(G, (mint::mod() - 1) / n);
    flt_ (u32, i, 1, n) root[i] = root[i - 1] * w;
  }

#pragma GCC diagnostic ignored "-Wsign-conversion"
  CEXP void dif(vec<mint> &f, u32 n = 0) const {
    assert(size());
    if (!n) n = size();
    if (f.size() < n) f.resize(n);
    assert(std::has_single_bit(n) && n <= size());
    for (u32 i = n / 2, d = 1; i; i /= 2, d *= 2)
      for (u32 j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint u, t;
        for (u32 k = 0; k < i; ++k, w += d) f[j | k] = (u = f[j | k]) + (t = f[i | j | k]), f[i | j | k] = (u - t) * (*w);
      }
  }
  CEXP void dit(vec<mint> &f, u32 n = 0) const {
    assert(size());
    if (!n) n = size();
    if (f.size() < n) f.resize(n);
    assert(std::has_single_bit(n) && n <= size());
    for (u32 i = 1, d = n / 2; d; i *= 2, d /= 2)
      for (u32 j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint t;
        for (u32 k = 0; k < i; ++k, w += d) f[i | j | k] = f[j | k] - (t = f[i | j | k] * (*w)), f[j | k] += t;
      }
    std::reverse(f.begin() + 1, f.end());
    const mint t = mint(n).inv();
    flt_ (u32, i, 0, n) f[i] *= t;
  }
#pragma GCC diagnostic warning "-Wsign-conversion"

 private:
  vec<mint> root;
};

}  // namespace tifa_libs::math

#endif