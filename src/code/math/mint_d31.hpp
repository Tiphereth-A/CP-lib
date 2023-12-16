#ifndef TIFALIBS_MATH_MINT_D31
#define TIFALIBS_MATH_MINT_D31

#include "../util/util.hpp"

namespace tifa_libs::math {

template <int>
class mint_d31 {
  u32 v_{};

  static constexpr u32 norm(i32 x) { return (u32)(x + (-(x < 0) & (i32)MOD)); }
  static constexpr u32 redc(u64 x) {
    u32 t = (u32)((x + (u64)((u32)(x)*R) * MOD_ODD) >> 32);
    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));
  }
  static constexpr u32 tsf(u32 x) { return redc((u64)(x % MOD_ODD) * R2) << OFFSET | (x & MASK); }

  static inline u32 R, R2, MOD, MOD_ODD, OFFSET, MASK;

 public:
  static constexpr void set_mod(u32 m) {
    assert(!(m == 1 || m >> 31));
    for (MOD = MOD_ODD = m, OFFSET = 0; (MOD_ODD & 1) == 0; ++OFFSET, MOD_ODD >>= 1)
      ;
    MASK = (1 << OFFSET) - 1;
    {
      u32 t = 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);
      iv *= t - MOD_ODD * iv, iv *= t - MOD_ODD * iv;
      R = iv * (MOD_ODD * iv - t);
    }
    R2 = (u32)(-(u64)(MOD_ODD) % MOD_ODD);
  }
  static constexpr u32 mod() { return MOD; }
  static constexpr i32 smod() { return (i32)MOD; }

  constexpr mint_d31() {}
  template <std::integral T>
  constexpr mint_d31(T v) : v_(tsf(norm((i32)(v % (T)smod())))) {}

  constexpr u32 val() const {
    u32 h = redc(v_ >> OFFSET);
    return ((h - v_) * R & MASK) * MOD_ODD + h;
  }
  constexpr i32 sval() const { return (i32)val(); }
  constexpr u32 &data() { return v_; }
  constexpr u32 const &data() const { return v_; }
  template <std::integral T>
  explicit constexpr operator T() const { return (T)(val()); }
  constexpr mint_d31 operator-() const {
    mint_d31 res;
    u32 h = v_ >> OFFSET;
    res.v_ = (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-v_ & MASK);
    return res;
  }
  constexpr mint_d31 inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = smod();
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return mint_d31(x1);
  }
  constexpr mint_d31 &operator+=(mint_d31 const &r) {
    u32 h = (v_ >> OFFSET) + (r.v_ >> OFFSET) - MOD_ODD;
    v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ + r.v_) & MASK);
    return *this;
  }
  constexpr mint_d31 &operator-=(mint_d31 const &r) {
    u32 h = (v_ >> OFFSET) - (r.v_ >> OFFSET);
    v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ - r.v_) & MASK);
    return *this;
  }
  constexpr mint_d31 &operator*=(mint_d31 const &r) {
    v_ = (redc((u64)(v_ >> OFFSET) * (r.v_ >> OFFSET)) << OFFSET) | ((v_ * r.v_) & MASK);
    return *this;
  }
  constexpr mint_d31 &operator/=(mint_d31 const &r) { return operator*=(r.inv()); }
  friend constexpr mint_d31 operator+(mint_d31 const &l, mint_d31 const &r) { return mint_d31(l) += r; }
  friend constexpr mint_d31 operator-(mint_d31 const &l, mint_d31 const &r) { return mint_d31(l) -= r; }
  friend constexpr mint_d31 operator*(mint_d31 const &l, mint_d31 const &r) { return mint_d31(l) *= r; }
  friend constexpr mint_d31 operator/(mint_d31 const &l, mint_d31 const &r) { return mint_d31(l) /= r; }
  friend constexpr bool operator==(mint_d31 const &l, mint_d31 const &r) { return l.v_ == r.v_; }
  friend constexpr bool operator!=(mint_d31 const &l, mint_d31 const &r) { return l.v_ != r.v_; }
  friend constexpr bool operator<(mint_d31 const &l, mint_d31 const &r) { return l.val() < r.val(); }
  friend std::istream &operator>>(std::istream &is, mint_d31 &r) {
    i32 x;
    is >> x;
    r = mint_d31(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint_d31 const &r) { return os << r.val(); }
  friend constexpr u32 abs(mint_d31 const &x) { return x.val(); }
};

}  // namespace tifa_libs::math

#endif