#ifndef TIFALIBS_MATH_MINTDATA_S30
#define TIFALIBS_MATH_MINTDATA_S30

#include "inverse.hpp"

namespace tifa_libs::math {

template <u32 MOD>
class mintdata_s30 {
  static constexpr u32 MOD2 = MOD << 1;
  static constexpr u32 R = get_r();
  static constexpr u32 R2 = -(u64)(MOD) % MOD;

  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);

  u32 v_{};

  static constexpr u32 reduce(u64 x) { return (u32)((x + (u64)((u32)(x)*R) * MOD) >> 32); }
  static constexpr u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31)); }
  static constexpr u32 get_r() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (MOD * iv - t);
  }

 public:
  using raw_type = u32;
  using sraw_type = i32;

  static constexpr raw_type mod() { return MOD; }
  static constexpr sraw_type smod() { return (sraw_type)MOD; }

  constexpr mintdata_s30() {}
  template <std::integral T>
  constexpr mintdata_s30(T v) : v_(reduce((u64)(v % smod() + smod()) * R2)) {}

  constexpr raw_type val() const { return norm(reduce(v_)); }
  constexpr sraw_type sval() const { return (sraw_type)norm(reduce(v_)); }
  constexpr raw_type &data() { return v_; }
  template <std::integral T>
  explicit constexpr operator T() const { return (T)(val()); }
  constexpr mintdata_s30 operator-() const {
    mintdata_s30 res;
    res.v_ = (MOD2 & -(v_ != 0)) - v_;
    return res;
  }
  constexpr mintdata_s30 &operator+=(mintdata_s30 const &r) {
    v_ += r.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr mintdata_s30 &operator-=(mintdata_s30 const &r) {
    v_ -= r.v_, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr mintdata_s30 &operator*=(mintdata_s30 const &r) {
    v_ = reduce((u64)(v_)*r.v_);
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif