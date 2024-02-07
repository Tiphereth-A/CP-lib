#ifndef TIFALIBS_MATH_MINTDATA_D63
#define TIFALIBS_MATH_MINTDATA_D63

#include "../util/util.hpp"

namespace tifa_libs::math {

template <int>
class mintdata_d63 {
  static inline u64 MOD, R, R2;

  u64 v_{};

  static constexpr u64 mul_high(u64 x, u64 y) {
    u64 a = x >> 32, b = (u32)(x), c = y >> 32, d = (u32)(y), ad = a * d, bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) + (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  static constexpr u64 redc_mul(u64 x, u64 y) {
    u64 res = mul_high(x, y) - mul_high(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  static constexpr u64 norm(i64 x) { return (u64)(x + (i64)(MOD & (u64)(-(x < 0)))); }

 public:
  using raw_type = u64;
  using sraw_type = i64;

  static constexpr void set_mod(raw_type m) {
    assert(!((m & 1) == 0 || m == 1 || m >> 63));
    MOD = m;
    raw_type t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;
    R = iv * (t - MOD * iv);
    R2 = -MOD % MOD;
    for (u32 i = 0; i != 64; ++i)
      if ((R2 *= 2) >= MOD) R2 -= MOD;
  }
  static constexpr raw_type mod() { return MOD; }
  static constexpr sraw_type smod() { return (sraw_type)MOD; }

  constexpr mintdata_d63() {}
  template <std::integral T>
  constexpr mintdata_d63(T v) : v_(redc_mul(norm(sraw_type(v % (T)smod())), R2)) {}

  constexpr raw_type val() const {
    raw_type res = -mul_high(v_ * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  constexpr sraw_type sval() const { return (sraw_type)val(); }
  constexpr raw_type &data() { return v_; }
  template <std::integral T>
  explicit constexpr operator T() const { return (T)(val()); }
  constexpr mintdata_d63 operator-() const {
    mintdata_d63 res;
    res.v_ = (MOD & -(v_ != 0)) - v_;
    return res;
  }
  constexpr mintdata_d63 &operator+=(mintdata_d63 const &r) {
    v_ += r.v_ - MOD, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  constexpr mintdata_d63 &operator-=(mintdata_d63 const &r) {
    v_ -= r.v_, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  constexpr mintdata_d63 &operator*=(mintdata_d63 const &r) {
    v_ = redc_mul(v_, r.v_);
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif