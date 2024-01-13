#ifndef TIFALIBS_MATH_MINTDATA_D31
#define TIFALIBS_MATH_MINTDATA_D31

#include "../util/util.hpp"

namespace tifa_libs::math {

template <int>
class mintdata_d31 {
  static inline u32 R, R2, MOD, MOD_ODD, OFFSET, MASK;

  u32 v_{};

  static constexpr u32 norm(i32 x) { return (u32)(x + (-(x < 0) & (i32)MOD)); }
  static constexpr u32 redc(u64 x) {
    u32 t = (u32)((x + (u64)((u32)(x)*R) * MOD_ODD) >> 32);
    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));
  }
  static constexpr u32 tsf(u32 x) { return redc((u64)(x % MOD_ODD) * R2) << OFFSET | (x & MASK); }

 public:
  using raw_type = u32;
  using sraw_type = i32;

  static constexpr void set_mod(raw_type m) {
    assert(!(m == 1 || m >> 31));
    for (MOD = MOD_ODD = m, OFFSET = 0; (MOD_ODD & 1) == 0; ++OFFSET, MOD_ODD >>= 1)
      ;
    MASK = (1 << OFFSET) - 1;
    {
      raw_type t = 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);
      iv *= t - MOD_ODD * iv, iv *= t - MOD_ODD * iv;
      R = iv * (MOD_ODD * iv - t);
    }
    R2 = (raw_type)(-(u64)(MOD_ODD) % MOD_ODD);
  }
  static constexpr raw_type mod() { return MOD; }
  static constexpr sraw_type smod() { return (sraw_type)MOD; }

  constexpr mintdata_d31() {}
  template <std::integral T>
  constexpr mintdata_d31(T v) : v_(tsf(norm((sraw_type)(v % (T)smod())))) {}

  constexpr raw_type val() const {
    raw_type h = redc(v_ >> OFFSET);
    return ((h - v_) * R & MASK) * MOD_ODD + h;
  }
  constexpr sraw_type sval() const { return (sraw_type)val(); }
  constexpr raw_type &data() { return v_; }
  template <std::integral T>
  explicit constexpr operator T() const { return (T)(val()); }
  constexpr mintdata_d31 operator-() const {
    mintdata_d31 res;
    raw_type h = v_ >> OFFSET;
    res.v_ = (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-v_ & MASK);
    return res;
  }
  constexpr mintdata_d31 &operator+=(mintdata_d31 const &r) {
    raw_type h = (v_ >> OFFSET) + (r.v_ >> OFFSET) - MOD_ODD;
    v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ + r.v_) & MASK);
    return *this;
  }
  constexpr mintdata_d31 &operator-=(mintdata_d31 const &r) {
    raw_type h = (v_ >> OFFSET) - (r.v_ >> OFFSET);
    v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ - r.v_) & MASK);
    return *this;
  }
  constexpr mintdata_d31 &operator*=(mintdata_d31 const &r) {
    v_ = (redc((u64)(v_ >> OFFSET) * (r.v_ >> OFFSET)) << OFFSET) | ((v_ * r.v_) & MASK);
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif