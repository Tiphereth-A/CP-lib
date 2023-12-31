#ifndef TIFALIBS_MATH_MINT_S30
#define TIFALIBS_MATH_MINT_S30

#include "inverse.hpp"

namespace tifa_libs::math {

template <u32 MOD>
class mint_s30 {
  u32 v_{};

  static constexpr u32 get_r() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (MOD * iv - t);
  }

 public:
  static constexpr u32 reduce(u64 x) { return (u32)((x + (u64)((u32)(x)*R) * MOD) >> 32); }
  static constexpr u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31)); }

  static constexpr u32 MOD2 = MOD << 1;
  static constexpr u32 R = get_r();
  static constexpr u32 R2 = -(u64)(MOD) % MOD;

  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);

  static constexpr u32 mod() { return MOD; }
  static constexpr i32 smod() { return (i32)MOD; }

  constexpr mint_s30() {}
  template <std::integral T>
  constexpr mint_s30(T v) : v_(reduce((u64)(v % smod() + smod()) * R2)) {}

  constexpr u32 val() const { return norm(reduce(v_)); }
  constexpr i32 sval() const { return (i32)norm(reduce(v_)); }
  constexpr u32 &data() { return v_; }
  constexpr u32 const &data() const { return v_; }
  template <std::integral T>
  explicit constexpr operator T() const { return (T)(val()); }
  constexpr mint_s30 operator-() const {
    mint_s30 res;
    res.v_ = (MOD2 & -(v_ != 0)) - v_;
    return res;
  }
  constexpr mint_s30 inv() const { return inverse(val(), mod()); }
  constexpr mint_s30 &operator+=(mint_s30 const &r) {
    v_ += r.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr mint_s30 &operator-=(mint_s30 const &r) {
    v_ -= r.v_, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr mint_s30 &operator*=(mint_s30 const &r) {
    v_ = reduce((u64)(v_)*r.v_);
    return *this;
  }
  constexpr mint_s30 &operator/=(mint_s30 const &r) { return operator*=(r.inv()); }
  friend constexpr mint_s30 operator+(mint_s30 const &l, mint_s30 const &r) { return mint_s30(l) += r; }
  friend constexpr mint_s30 operator-(mint_s30 const &l, mint_s30 const &r) { return mint_s30(l) -= r; }
  friend constexpr mint_s30 operator*(mint_s30 const &l, mint_s30 const &r) { return mint_s30(l) *= r; }
  friend constexpr mint_s30 operator/(mint_s30 const &l, mint_s30 const &r) { return mint_s30(l) /= r; }
  friend constexpr bool operator==(mint_s30 const &l, mint_s30 const &r) { return norm(l.v_) == norm(r.v_); }
  friend constexpr auto operator<=>(mint_s30 const &l, mint_s30 const &r) { return l.sval() - r.sval(); }
  friend std::istream &operator>>(std::istream &is, mint_s30 &r) {
    i32 x;
    is >> x;
    r = mint_s30(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint_s30 const &r) { return os << r.val(); }
  friend constexpr u32 abs(mint_s30 const &x) { return x.val(); }
};

}  // namespace tifa_libs::math

#endif