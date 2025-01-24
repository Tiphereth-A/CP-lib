#ifndef TIFALIBS_CONV_NTT
#define TIFALIBS_CONV_NTT

#include "../math/qpow.hpp"
#include "../nt/proot.hpp"

namespace tifa_libs::math {

template <class mint>
struct NTT {
  using data_t = mint;

  static_assert(is_prime(mint::mod()) && (mint::mod() & 3) == 1, "MOD must be prime with 4k+1");
  static CEXP u64 R = std::countr_zero(mint::mod() - 1), max_size = 1_u64 << R;
  static CEXP mint G = proot(mint::mod());

 private:
  static inline arr<mint, R + 1> root, iroot, inv2;
  static inline arr<mint, R - 1> rate, irate;
  u32 sz;

 public:
  CEXPE NTT() NE : sz() {
    if (inv2[0].val()) return;
    root[R] = qpow(G, mint::mod() >> R), iroot[R] = root[R].inv();
    for (u32 i = R - 1; ~i; --i) {
      root[i] = root[i + 1] * root[i + 1];
      iroot[i] = iroot[i + 1] * iroot[i + 1];
    }
    mint prod(1), iprod(1);
    flt_ (u32, i, 0, R - 1) {
      rate[i] = prod * root[i + 2];
      irate[i] = iprod * iroot[i + 2];
      prod *= iroot[i + 2], iprod *= root[i + 2];
    }
    mint i2 = mint::mod() / 2 + 1;
    inv2[0] = 1;
    flt_ (u32, i, 0, R) inv2[i + 1] = inv2[i] * i2;
  }

  CEXP u32 size() CNE { return sz; }
  CEXP void bzr(u32 len = max_size) NE {
    const u32 n = std::bit_ceil(len);
    assert(n <= max_size), sz = n;
  }
  CEXP void dif(vec<mint> &f, u32 n = 0) CNE {
    if (assert(size()); !n) n = size();
    if (f.size() < n) f.resize(n);
    assert(std::has_single_bit(n) && n <= size());
    const u32 l = (u32)std::countr_zero(n);
    flt_ (u32, i, 0, l) {
      const u32 w = 1 << (l - 1 - i), b = 1 << i;
      mint z = 1;
      flt_ (u32, j, 0, b) {
        const u32 o = j << (l - i);
        flt_ (u32, k, 0, w) {
          mint x = f[o + k], y = f[o + k + w] * z;
          f[o + k] = x + y, f[o + k + w] = x - y;
        }
        z *= rate[(u32)std::countr_zero(~j)];
      }
    }
  }
  CEXP void dit(vec<mint> &f, u32 n = 0) CNE {
    assert(size());
    if (!n) n = size();
    if (f.size() < n) f.resize(n);
    assert(std::has_single_bit(n) && n <= size());
    const u32 l = (u32)std::countr_zero(n);
    for (u32 i = l - 1; ~i; --i) {
      const u32 w = 1 << (l - 1 - i), b = 1 << i;
      mint z = 1;
      flt_ (u32, j, 0, b) {
        const u32 o = j << (l - i);
        flt_ (u32, k, 0, w) {
          mint x = f[o + k], y = f[o + k + w];
          f[o + k] = x + y, f[o + k + w] = (x - y) * z;
        }
        z *= irate[(u32)std::countr_zero(~j)];
      }
    }
    flt_ (u32, i, 0, n) f[i] *= inv2[l];
  }
};

}  // namespace tifa_libs::math

#endif