#ifndef TIFALIBS_MATH_MINTDATA_SS
#define TIFALIBS_MATH_MINTDATA_SS

#include "../util/util.hpp"

namespace tifa_libs::math {

template <u32 MOD>
class mintdata_ss {
  static_assert(MOD >= 1);

  u32 v_;

 public:
  using raw_type = u32;
  using sraw_type = i32;
  static constexpr raw_type mod() { return MOD; }
  static constexpr sraw_type smod() { return (sraw_type)MOD; }

  constexpr mintdata_ss() : v_(0) {}
  template <std::signed_integral T>
  constexpr mintdata_ss(T v) : mintdata_ss() {
    i64 x = (i64)(v % (i64)mod());
    v_ = (raw_type)(x + (x < 0 ? mod() : 0));
  }
  template <std::unsigned_integral T>
  constexpr mintdata_ss(T v) : v_((raw_type)(v % mod())) {}

  constexpr raw_type val() const { return v_; }
  constexpr sraw_type sval() const { return (sraw_type)v_; }
  constexpr raw_type &data() { return v_; }
  constexpr mintdata_ss operator-() const { return mintdata_ss(-sval()); }
  constexpr mintdata_ss &operator+=(mintdata_ss const &r) {
    v_ += r.v_;
    if (v_ >= mod()) v_ -= mod();
    return *this;
  }
  constexpr mintdata_ss &operator-=(mintdata_ss const &r) {
    v_ -= r.v_;
    if (v_ >= mod()) v_ += mod();
    return *this;
  }
  constexpr mintdata_ss &operator*=(mintdata_ss const &r) {
    v_ = (u32)((u64)v_ * r.v_ % mod());
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif