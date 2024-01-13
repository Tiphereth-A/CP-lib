#ifndef TIFALIBS_MATH_MINTDATA_DS
#define TIFALIBS_MATH_MINTDATA_DS

#include "barrett.hpp"

namespace tifa_libs::math {

template <isz>
class mintdata_ds {
  u32 v_;
  static inline barrett bt_;

 public:
  using raw_type = u32;
  using sraw_type = i32;
  static constexpr raw_type mod() { return bt_.umod(); }
  static constexpr sraw_type smod() { return (sraw_type)bt_.umod(); }
  static constexpr void set_mod(raw_type m) {
    assert(1 <= m);
    bt_ = barrett(m);
  }

  constexpr mintdata_ds() : v_(0) {}
  template <std::signed_integral T>
  constexpr mintdata_ds(T v) : mintdata_ds() {
    i64 x = (i64)(v % (i64)mod());
    v_ = (raw_type)(x + (x < 0 ? mod() : 0));
  }
  template <std::unsigned_integral T>
  constexpr mintdata_ds(T v) : v_((raw_type)(v % mod())) {}
  constexpr raw_type val() const { return v_; }
  constexpr sraw_type sval() const { return (sraw_type)v_; }
  constexpr raw_type &data() { return v_; }
  constexpr mintdata_ds operator-() const { return mintdata_ds(-sval()); }
  constexpr mintdata_ds &operator+=(mintdata_ds const &r) {
    v_ += r.v_;
    if (v_ >= mod()) v_ -= mod();
    return *this;
  }
  constexpr mintdata_ds &operator-=(mintdata_ds const &r) {
    v_ -= r.v_;
    if (v_ >= mod()) v_ += mod();
    return *this;
  }
  constexpr mintdata_ds &operator*=(mintdata_ds const &r) {
    v_ = bt_.mul(v_, r.v_);
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif