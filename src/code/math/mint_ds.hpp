#ifndef TIFALIBS_MATH_MINT_DS
#define TIFALIBS_MATH_MINT_DS

#include "barrett.hpp"
#include "inverse.hpp"

namespace tifa_libs::math {

template <isz>
class mint_ds {
 protected:
  u32 v_;
  static inline barrett bt_;

 public:
  static constexpr u32 mod() { return bt_.umod(); }
  static constexpr i32 smod() { return (i32)bt_.umod(); }
  //! MUST be called first
  //! set module with same ID
  static constexpr void set_mod(u32 m) {
    assert(1 <= m);
    bt_ = barrett(m);
  }
  static constexpr mint_ds raw(u32 v) {
    mint_ds x;
    x.v_ = v;
    return x;
  }
  constexpr mint_ds() : v_(0) {}
  template <std::signed_integral T>
  constexpr mint_ds(T v) : mint_ds() {
    i64 x = (i64)(v % (i64)mod());
    v_ = (u32)(x + (x < 0 ? mod() : 0));
  }
  template <std::unsigned_integral T>
  constexpr mint_ds(T v) : v_((u32)(v % mod())) {}
  friend std::istream &operator>>(std::istream &is, mint_ds &x) {
    i64 xx;
    is >> xx;
    xx %= mod();
    x.v_ = (u32)(xx + (xx < 0 ? mod() : 0));
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint_ds const &x) { return os << x.v_; }
  constexpr u32 val() const { return v_; }
  constexpr i32 sval() const { return (i32)v_; }
  explicit constexpr operator u32() const { return val(); }
  constexpr u32 &data() { return v_; }
  constexpr mint_ds &operator++() {
    if (++v_ == mod()) v_ = 0;
    return *this;
  }
  constexpr mint_ds &operator--() {
    if (!v_) v_ = mod();
    --v_;
    return *this;
  }
  constexpr mint_ds operator++(int) {
    mint_ds result = *this;
    ++*this;
    return result;
  }
  constexpr mint_ds operator--(int) {
    mint_ds result = *this;
    --*this;
    return result;
  }
  constexpr mint_ds &operator+=(mint_ds const &r) {
    v_ += r.v_;
    if (v_ >= mod()) v_ -= mod();
    return *this;
  }
  constexpr mint_ds &operator-=(mint_ds const &r) {
    v_ -= r.v_;
    if (v_ >= mod()) v_ += mod();
    return *this;
  }
  constexpr mint_ds &operator*=(mint_ds const &r) {
    v_ = bt_.mul(v_, r.v_);
    return *this;
  }
  constexpr mint_ds &operator/=(mint_ds const &r) { return *this = *this * r.inv(); }
  constexpr mint_ds operator+() const { return *this; }
  constexpr mint_ds operator-() const { return mint_ds() - *this; }
  constexpr mint_ds inv() const { return inverse(v_, mod()); }
  friend constexpr mint_ds operator+(mint_ds l, mint_ds const &r) { return l += r; }
  friend constexpr mint_ds operator-(mint_ds l, mint_ds const &r) { return l -= r; }
  friend constexpr mint_ds operator*(mint_ds l, mint_ds const &r) { return l *= r; }
  friend constexpr mint_ds operator/(mint_ds l, mint_ds const &r) { return l /= r; }
  friend constexpr bool operator==(mint_ds const &l, mint_ds const &r) { return l.v_ == r.v_; }
  friend constexpr auto operator<=>(mint_ds const &l, mint_ds const &r) { return (i32)l.v_ - (i32)r.v_; }
};

}  // namespace tifa_libs::math

#endif