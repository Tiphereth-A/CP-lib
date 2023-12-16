#ifndef TIFALIBS_MATH_MINT_D63
#define TIFALIBS_MATH_MINT_D63

#include "../util/util.hpp"

namespace tifa_libs::math {

template <int>
class mint_d63 {
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

  static inline u64 MOD, R, R2;

 public:
  static constexpr void set_mod(u64 m) {
    assert(!((m & 1) == 0 || m == 1 || m >> 63));
    MOD = m;
    {
      u64 t = 2, iv = MOD * (t - MOD * MOD);
      iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;
      R = iv * (t - MOD * iv);
    }
    {
      R2 = -MOD % MOD;
      for (int i = 0; i != 64; ++i)
        if ((R2 *= 2) >= MOD) R2 -= MOD;
    }
  }
  static constexpr u64 mod() { return MOD; }
  static constexpr i64 smod() { return (i64)MOD; }

  constexpr mint_d63() {}
  template <std::integral T>
  constexpr mint_d63(T v) : v_(redc_mul(norm(i64(v % (T)smod())), R2)) {}

  constexpr u64 val() const {
    u64 res = -mul_high(v_ * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  constexpr i64 sval() const { return (i64)val(); }
  constexpr u64 &data() { return v_; }
  constexpr u64 const &data() const { return v_; }
  template <std::integral T>
  explicit constexpr operator T() const { return (T)(val()); }
  constexpr mint_d63 operator-() const {
    mint_d63 res;
    res.v_ = (MOD & -(v_ != 0)) - v_;
    return res;
  }
  constexpr mint_d63 inv() const {
    i64 x1 = 1, x3 = 0, a = sval(), b = smod();
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return mint_d63(x1);
  }
  constexpr mint_d63 &operator+=(mint_d63 const &r) {
    v_ += r.v_ - MOD, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  constexpr mint_d63 &operator-=(mint_d63 const &r) {
    v_ -= r.v_, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  constexpr mint_d63 &operator*=(mint_d63 const &r) {
    v_ = redc_mul(v_, r.v_);
    return *this;
  }
  constexpr mint_d63 &operator/=(mint_d63 const &r) {
    return operator*=(r.inv());
  }
  friend constexpr mint_d63 operator+(mint_d63 const &l, mint_d63 const &r) { return mint_d63(l) += r; }
  friend constexpr mint_d63 operator-(mint_d63 const &l, mint_d63 const &r) { return mint_d63(l) -= r; }
  friend constexpr mint_d63 operator*(mint_d63 const &l, mint_d63 const &r) { return mint_d63(l) *= r; }
  friend constexpr mint_d63 operator/(mint_d63 const &l, mint_d63 const &r) { return mint_d63(l) /= r; }
  friend constexpr bool operator==(mint_d63 const &l, mint_d63 const &r) { return l.v_ == r.v_; }
  friend constexpr bool operator!=(mint_d63 const &l, mint_d63 const &r) { return l.v_ != r.v_; }
  friend constexpr bool operator<(mint_d63 const &l, mint_d63 const &r) { return l.val() < r.val(); }
  friend std::istream &operator>>(std::istream &is, mint_d63 &r) {
    i64 x;
    is >> x;
    r = mint_d63(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint_d63 const &r) { return os << r.val(); }
  friend constexpr u64 abs(mint_d63 const &x) { return x.val(); }
};

}  // namespace tifa_libs::math

#endif