#ifndef TIFA_LIBS_MATH_MINT_SS
#define TIFA_LIBS_MATH_MINT_SS

#include "inverse.hpp"

namespace tifa_libs::math {

template <u32 MOD>
class mint_ss {
  static_assert(MOD >= 1);

  u32 v_;

 public:
  constexpr static u32 mod() { return MOD; }
  constexpr static mint_ss raw(u32 v) {
    mint_ss x;
    x.v_ = v;
    return x;
  }
  constexpr mint_ss() : v_(0) {}
  template <class T, std::enable_if_t<std::is_integral<T>::value && std::is_signed<T>::value> * = nullptr>
  constexpr mint_ss(T v) : mint_ss() {
    i64 x = (i64)(v % (i64)mod());
    v_ = (u32)(x + (x < 0 ? mod() : 0));
  }
  template <class T, std::enable_if_t<std::is_integral<T>::value && std::is_unsigned<T>::value> * = nullptr>
  constexpr mint_ss(T v) : v_((u32)(v % mod())) {}
  friend std::istream &operator>>(std::istream &is, mint_ss &x) {
    i64 xx;
    is >> xx;
    xx %= mod();
    x.v_ = (u32)(xx + (xx < 0 ? mod() : 0));
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint_ss &x) { return os << x.v_; }
  constexpr const u32 &val() const { return v_; }
  constexpr i32 sval() const { return (i32)v_; }
  constexpr explicit operator u32() const { return val(); }
  constexpr u32 &data() { return v_; }
  constexpr mint_ss &operator++() {
    if (++v_ == mod()) v_ = 0;
    return *this;
  }
  constexpr mint_ss &operator--() {
    if (!v_) v_ = mod();
    --v_;
    return *this;
  }
  constexpr mint_ss operator++(int) {
    mint_ss result = *this;
    ++*this;
    return result;
  }
  constexpr mint_ss operator--(int) {
    mint_ss result = *this;
    --*this;
    return result;
  }
  constexpr mint_ss &operator+=(const mint_ss &r) {
    v_ += r.v_;
    if (v_ >= mod()) v_ -= mod();
    return *this;
  }
  constexpr mint_ss &operator-=(const mint_ss &r) {
    v_ -= r.v_;
    if (v_ >= mod()) v_ += mod();
    return *this;
  }
  constexpr mint_ss &operator*=(const mint_ss &r) {
    v_ = (u32)((u64)v_ * r.v_ % mod());
    return *this;
  }
  constexpr mint_ss &operator/=(const mint_ss &r) { return *this = *this * r.inv(); }
  constexpr mint_ss operator+() const { return *this; }
  constexpr mint_ss operator-() const { return mint_ss() - *this; }
  constexpr mint_ss inv() const { return inverse(v_, mod()); }
  constexpr friend mint_ss operator+(mint_ss l, const mint_ss &r) { return l += r; }
  constexpr friend mint_ss operator-(mint_ss l, const mint_ss &r) { return l -= r; }
  constexpr friend mint_ss operator*(mint_ss l, const mint_ss &r) { return l *= r; }
  constexpr friend mint_ss operator/(mint_ss l, const mint_ss &r) { return l /= r; }
  constexpr friend bool operator==(const mint_ss &l, const mint_ss &r) { return l.v_ == r.v_; }
  constexpr friend bool operator!=(const mint_ss &l, const mint_ss &r) { return l.v_ != r.v_; }
  constexpr friend bool operator<(const mint_ss &l, const mint_ss &r) { return l.v_ < r.v_; }
};

}  // namespace tifa_libs::math

#endif