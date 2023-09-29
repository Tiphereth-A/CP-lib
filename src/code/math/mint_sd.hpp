#ifndef TIFA_LIBS_MATH_MINT_SD
#define TIFA_LIBS_MATH_MINT_SD

#include "barrett.hpp"
#include "inverse.hpp"

namespace tifa_libs::math {

template <ptrdiff_t ID = -1>
class mint_sd {
protected:
  u32 v_;
  static inline barrett bt_;

public:
  constexpr static u32 mod() { return bt_.umod(); }
  //! MUST be called first
  //! set module with same ID
  constexpr static void set_mod(u32 m) {
    assert(1 <= m);
    bt_ = barrett(m);
  }
  constexpr static mint_sd raw(u32 v) {
    mint_sd x;
    x.v_ = v;
    return x;
  }
  constexpr mint_sd():
    v_(0) {}
  template <class T, std::enable_if_t<std::is_integral<T>::value && std::is_signed<T>::value> * = nullptr>
  constexpr mint_sd(T v):
    mint_sd() {
    i64 x = (i64)(v % (i64)mod());
    v_ = (u32)(x + (x < 0 ? mod() : 0));
  }
  template <class T, std::enable_if_t<std::is_integral<T>::value && std::is_unsigned<T>::value> * = nullptr>
  constexpr mint_sd(T v):
    v_((u32)(v % mod())) {}
  friend std::istream &operator>>(std::istream &is, mint_sd &x) {
    i64 xx;
    is >> xx;
    xx %= mod();
    x.v_ = (u32)(xx + (xx < 0 ? mod() : 0));
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint_sd &x) { return os << x.v_; }
  constexpr const u32 &val() const { return v_; }
  constexpr explicit operator u32() const { return val(); }
  constexpr u32 &data() { return v_; }
  constexpr mint_sd &operator++() {
    if (++v_ == mod()) v_ = 0;
    return *this;
  }
  constexpr mint_sd &operator--() {
    if (!v_) v_ = mod();
    --v_;
    return *this;
  }
  constexpr mint_sd operator++(int) {
    mint_sd result = *this;
    ++*this;
    return result;
  }
  constexpr mint_sd operator--(int) {
    mint_sd result = *this;
    --*this;
    return result;
  }
  constexpr mint_sd &operator+=(const mint_sd &r) {
    v_ += r.v_;
    if (v_ >= mod()) v_ -= mod();
    return *this;
  }
  constexpr mint_sd &operator-=(const mint_sd &r) {
    v_ -= r.v_;
    if (v_ >= mod()) v_ += mod();
    return *this;
  }
  constexpr mint_sd &operator*=(const mint_sd &r) {
    v_ = bt_.mul(v_, r.v_);
    return *this;
  }
  constexpr mint_sd &operator/=(const mint_sd &r) { return *this = *this * inv(r); }
  constexpr mint_sd operator+() const { return *this; }
  constexpr mint_sd operator-() const { return mint_sd() - *this; }
  constexpr friend mint_sd inv(const mint_sd &x) { return inverse(x.v_, mod()); }
  constexpr friend mint_sd operator+(mint_sd l, const mint_sd &r) { return l += r; }
  constexpr friend mint_sd operator-(mint_sd l, const mint_sd &r) { return l -= r; }
  constexpr friend mint_sd operator*(mint_sd l, const mint_sd &r) { return l *= r; }
  constexpr friend mint_sd operator/(mint_sd l, const mint_sd &r) { return l /= r; }
  constexpr friend bool operator==(const mint_sd &l, const mint_sd &r) { return l.v_ == r.v_; }
  constexpr friend bool operator!=(const mint_sd &l, const mint_sd &r) { return l.v_ != r.v_; }
  constexpr friend bool operator<(const mint_sd &l, const mint_sd &r) { return l.v_ < r.v_; }
};

}  // namespace tifa_libs::math

#endif