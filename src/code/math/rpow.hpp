#ifndef TIFA_LIBS_MATH_RPOW
#define TIFA_LIBS_MATH_RPOW

#include "mul_mod_u.hpp"

namespace tifa_libs::math {

class rpow {
  vec<u64> b0, b1;
  u64 b_, m_;

 public:
  explicit rpow() : b0(65536), b1(65536), b_(), m_() {}
  rpow(u64 base_, u32 mod_) : rpow() { reset(base_, mod_); }

  void reset(u64 base, u32 mod) {
    if (b_ == base % mod && m_ == mod) return;
    b_ = base % mod;
    m_ = mod;
    b0[0] = b1[0] = 1;
    for (usz i = 1; i < 65536; ++i) b0[i] = mul_mod_u(b0[i - 1], b_, m_);
    u64 _(mul_mod_u(b0.back(), b_, m_));
    for (usz i = 1; i < 65536; ++i) b1[i] = mul_mod_u(b1[i - 1], _, m_);
  }

  void swap(rpow& r) {
    b0.swap(r.b0);
    b1.swap(r.b1);
    std::swap(b_, r.b_);
    std::swap(m_, r.m_);
  }

  constexpr u64 base() const { return b_; }
  constexpr u64 mod() const { return m_; }

  u64 operator()(u32 x) const { return mul_mod_u(b0[x & 0xff], b1[x >> 16], m_); }
};

}  // namespace tifa_libs::math

#endif