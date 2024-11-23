#ifndef TIFALIBS_MATH_MINT_D63
#define TIFALIBS_MATH_MINT_D63

#include "../util/traits.hpp"

namespace tifa_libs::math {

template <u64 ID>
class mint_d63 {
  static inline u64 MOD, R, R2;
  static CEXP u64 mul_h(u64 x, u64 y) {
    u64 a = x >> 32, b = (u32)x, c = y >> 32, d = (u32)y, ad = a * d, bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) + (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  static CEXP u64 redc_mul(u64 x, u64 y) {
    u64 res = mul_h(x, y) - mul_h(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  static CEXP u64 norm(i64 x) { return u64(x + i64(MOD & u64(-(x < 0)))); }

 public:
  static CEXP bool FIXED_MOD = false;
  static CEXP void set_mod(u64 m) {
    assert(!((m & 1) == 0 || m == 1 || m >> 63)), MOD = m;
    u64 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv, R = iv * (t - MOD * iv), R2 = -MOD % MOD;
    flt_ (u32, i, 0, 64)
      if ((R2 *= 2) >= MOD) R2 -= MOD;
  }

 protected:
  using raw_t = u64;
  raw_t v_;
  CEXP mint_d63() : v_{} {}
  CEXP mint_d63(int_c auto v) : v_{mod(v)} {}
  template <int_c T>
  static CEXP raw_t mod(T v) { return redc_mul(norm(i64(v % (std::conditional_t<sint_c<T>, i64, u64>)mod())), R2); }
  static CEXP raw_t mod() { return MOD; }
  CEXP raw_t val() const {
    raw_t res = -mul_h(v_ * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  CEXP raw_t &data() { return v_; }
  template <class mint>
  CEXP auto neg() const {
    mint res;
    return res.v_ = (MOD & -(v_ != 0)) - v_, res;
  }
  CEXP void add(mint_d63 CR r) { v_ += r.v_ - MOD, v_ += MOD & -(v_ >> 63); }
  CEXP void sub(mint_d63 CR r) { v_ -= r.v_, v_ += MOD & -(v_ >> 63); }
  CEXP void mul(mint_d63 CR r) { v_ = redc_mul(v_, r.v_); }
};

}  // namespace tifa_libs::math

#endif