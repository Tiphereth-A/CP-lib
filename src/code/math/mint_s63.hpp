#ifndef TIFA_LIBS_MATH_MINT_S63
#define TIFA_LIBS_MATH_MINT_S63

#include "../util/util.hpp"

namespace tifa_libs::math {

template <u64 MOD>
class mint_s63 {
  u64 v_{};

  static constexpr u64 get_r() {
    u64 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (t - MOD * iv);
  }
  static constexpr u64 get_r2() {
    u64 iv = -MOD % MOD;
    for (int i = 0; i != 64; ++i)
      if ((iv *= 2) >= MOD) iv -= MOD;
    return iv;
  }
  static constexpr u64 mul_high(u64 x, u64 y) {
    u64 a = x >> 32, b = (u32)(x), c = y >> 32, d = (u32)(y), ad = a * d, bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) + (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  static constexpr u64 redc_mul(u64 x, u64 y) {
    u64 res = mul_high(x, y) - mul_high(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  static constexpr u64 norm(i64 x) { return x + (MOD & -(x < 0)); }

  static constexpr u64 R = get_r();
  static constexpr u64 R2 = get_r2();
  static constexpr i64 SMOD = (i64)(MOD);

  static_assert(MOD & 1);
  static_assert(R * MOD == 1);
  static_assert((MOD >> 63) == 0);
  static_assert(MOD != 1);

 public:
  static constexpr u64 mod() { return MOD; }
  static constexpr i64 smod() { return SMOD; }
  constexpr mint_s63() {}
  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  constexpr mint_s63(T v) : v_(redc_mul(norm(v % SMOD), R2)) {}
  constexpr u64 val() const {
    u64 res = -mul_high(v_ * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  constexpr i64 sval() const { return val(); }
  constexpr bool is_zero() const { return v_ == 0; }
  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  explicit constexpr operator T() const { return (T)(val()); }
  constexpr mint_s63 operator-() const {
    mint_s63 res;
    res.v_ = (MOD & -(v_ != 0)) - v_;
    return res;
  }
  constexpr mint_s63 inv() const {
    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return mint_s63(x1);
  }
  constexpr mint_s63 &operator+=(const mint_s63 &rhs) {
    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  constexpr mint_s63 &operator-=(const mint_s63 &rhs) {
    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  constexpr mint_s63 &operator*=(const mint_s63 &rhs) {
    v_ = redc_mul(v_, rhs.v_);
    return *this;
  }
  constexpr mint_s63 &operator/=(const mint_s63 &rhs) { return operator*=(rhs.inv()); }
  constexpr mint_s63 pow(u64 e) const {
    for (mint_s63 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  constexpr void swap(mint_s63 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend constexpr mint_s63 operator+(const mint_s63 &lhs, const mint_s63 &rhs) { return mint_s63(lhs) += rhs; }
  friend constexpr mint_s63 operator-(const mint_s63 &lhs, const mint_s63 &rhs) { return mint_s63(lhs) -= rhs; }
  friend constexpr mint_s63 operator*(const mint_s63 &lhs, const mint_s63 &rhs) { return mint_s63(lhs) *= rhs; }
  friend constexpr mint_s63 operator/(const mint_s63 &lhs, const mint_s63 &rhs) { return mint_s63(lhs) /= rhs; }
  friend constexpr bool operator==(const mint_s63 &lhs, const mint_s63 &rhs) { return lhs.v_ == rhs.v_; }
  friend constexpr bool operator!=(const mint_s63 &lhs, const mint_s63 &rhs) { return lhs.v_ != rhs.v_; }
  friend constexpr bool operator<(const mint_s63 &lhs, const mint_s63 &rhs) { return lhs.val() < rhs.val(); }
  friend std::istream &operator>>(std::istream &is, mint_s63 &rhs) {
    i64 x;
    is >> x;
    rhs = mint_s63(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint_s63 &rhs) { return os << rhs.val(); }
  friend constexpr u64 abs(mint_s63 const &x) { return x.val(); }
};

}  // namespace tifa_libs::math

#endif