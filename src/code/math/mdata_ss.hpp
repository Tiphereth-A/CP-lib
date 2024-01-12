#ifndef TIFALIBS_MATH_MDATA_SS
#define TIFALIBS_MATH_MDATA_SS

#include "../util/util.hpp"

namespace tifa_libs::math {

template <u32 MOD>
class mdata_ss {
  static_assert(MOD >= 1);

  u32 v_;

 public:
  using raw_type = u32;
  using sraw_type = i32;
  static constexpr raw_type mod() { return MOD; }
  static constexpr sraw_type smod() { return (sraw_type)MOD; }

  constexpr mdata_ss() : v_(0) {}
  template <std::signed_integral T>
  constexpr mdata_ss(T v) : mdata_ss() {
    i64 x = (i64)(v % (i64)mod());
    v_ = (raw_type)(x + (x < 0 ? mod() : 0));
  }
  template <std::unsigned_integral T>
  constexpr mdata_ss(T v) : v_((raw_type)(v % mod())) {}

  constexpr raw_type val() const { return v_; }
  constexpr sraw_type sval() const { return (sraw_type)v_; }
  constexpr raw_type &data() { return v_; }
  constexpr mint_ss operator-() const { return mint_ss() - *this; }
  constexpr mdata_ss &operator+=(mdata_ss const &r) {
    v_ += r.v_;
    if (v_ >= mod()) v_ -= mod();
    return *this;
  }
  constexpr mdata_ss &operator-=(mdata_ss const &r) {
    v_ -= r.v_;
    if (v_ >= mod()) v_ += mod();
    return *this;
  }
  constexpr mdata_ss &operator*=(mdata_ss const &r) {
    v_ = (u32)((u64)v_ * r.v_ % mod());
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif