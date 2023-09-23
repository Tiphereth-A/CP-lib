#ifndef TIFA_LIBS_MATH_MINT_D31
#define TIFA_LIBS_MATH_MINT_D31

#include "../util/util.hpp"

namespace tifa_libs::math {

template <int>
class mint_d31 {
  u32 v_{};

  static inline u32 norm(i32 x) { return x + (-(x < 0) & MOD); }
  static inline u32 redc(u64 x) {
    u32 t = (x + (u64)((u32)(x)*R) * MOD_ODD) >> 32;
    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));
  }
  static inline u32 tsf(u32 x) { return redc((u64)(x % MOD_ODD) * R2) << OFFSET | (x & MASK); }

  static u32 R, R2, MOD, MOD_ODD, OFFSET, MASK;
  static i32 SMOD;

public:
  static inline bool set_mod(u32 m) {
    if (m == 1 || m >> 31 != 0) return false;
    for (MOD = MOD_ODD = m, OFFSET = 0; (MOD_ODD & 1) == 0; ++OFFSET, MOD_ODD >>= 1) {}
    MASK = (1 << OFFSET) - 1, SMOD = (i32)(MOD);
    {
      u32 t = 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);
      iv *= t - MOD_ODD * iv, iv *= t - MOD_ODD * iv;
      R = iv * (MOD_ODD * iv - t);
    }
    R2 = -(u64)(MOD_ODD) % MOD_ODD;
    return true;
  }
  static inline u32 mod() { return MOD; }
  static inline i32 smod() { return SMOD; }
  mint_d31() {}
  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  mint_d31(T v):
    v_(tsf(norm(v % SMOD))) {}
  u32 val() const {
    u32 h = redc(v_ >> OFFSET);
    return ((h - v_) * R & MASK) * MOD_ODD + h;
  }
  i32 sval() const { return val(); }
  bool is_zero() const { return v_ == 0; }
  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  explicit operator T() const { return (T)(val()); }
  mint_d31 operator-() const {
    mint_d31 res;
    u32 h = v_ >> OFFSET;
    res.v_ = (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-v_ & MASK);
    return res;
  }
  mint_d31 inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return mint_d31(x1);
  }
  mint_d31 &operator+=(const mint_d31 &rhs) {
    u32 h = (v_ >> OFFSET) + (rhs.v_ >> OFFSET) - MOD_ODD;
    v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ + rhs.v_) & MASK);
    return *this;
  }
  mint_d31 &operator-=(const mint_d31 &rhs) {
    u32 h = (v_ >> OFFSET) - (rhs.v_ >> OFFSET);
    v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ - rhs.v_) & MASK);
    return *this;
  }
  mint_d31 &operator*=(const mint_d31 &rhs) {
    v_ = (redc((u64)(v_ >> OFFSET) * (rhs.v_ >> OFFSET)) << OFFSET) | ((v_ * rhs.v_) & MASK);
    return *this;
  }
  mint_d31 &operator/=(const mint_d31 &rhs) { return operator*=(rhs.inv()); }
  mint_d31 pow(u64 e) const {
    for (mint_d31 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  void swap(mint_d31 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend mint_d31 operator+(const mint_d31 &lhs, const mint_d31 &rhs) { return mint_d31(lhs) += rhs; }
  friend mint_d31 operator-(const mint_d31 &lhs, const mint_d31 &rhs) { return mint_d31(lhs) -= rhs; }
  friend mint_d31 operator*(const mint_d31 &lhs, const mint_d31 &rhs) { return mint_d31(lhs) *= rhs; }
  friend mint_d31 operator/(const mint_d31 &lhs, const mint_d31 &rhs) { return mint_d31(lhs) /= rhs; }
  friend bool operator==(const mint_d31 &lhs, const mint_d31 &rhs) { return lhs.v_ == rhs.v_; }
  friend bool operator!=(const mint_d31 &lhs, const mint_d31 &rhs) { return lhs.v_ != rhs.v_; }
  friend std::istream &operator>>(std::istream &is, mint_d31 &rhs) {
    i32 x;
    is >> x;
    rhs = mint_d31(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint_d31 &rhs) { return os << rhs.val(); }
  friend constexpr u32 abs(mint_d31 const &x) { return x.val(); }
};

}  // namespace tifa_libs::math

#endif