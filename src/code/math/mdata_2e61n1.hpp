#ifndef TIFALIBS_MATH_MDATA_2E61N1
#define TIFALIBS_MATH_MDATA_2E61N1

#include "../util/traits.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

class mdata_2e61n1 {
  u64 v_{};
  static constexpr u64 MOD = (1ull << 61) - 1;
  static constexpr u64 _30 = (1 << 30) - 1, _31 = (1u << 31) - 1;

  // clang-format off
  template <uint_c T>
  static constexpr u64 mod_(T x) { return x < MOD ? (u64)x : (x = (x & MOD) + ((u64)x >> 61)) > MOD ? x - MOD : (u64)x; }
  template <sint_c T>
  static constexpr u64 mod_(T x) { return x >= 0 ? mod_(to_uint_t<T>(x)) : MOD - mod_(to_uint_t<T>(-x)); }
  // clang-format on

 public:
  using raw_type = u64;
  using sraw_type = i64;
  static constexpr raw_type mod() { return MOD; }
  static constexpr sraw_type smod() { return (sraw_type)MOD; }

  constexpr mdata_2e61n1() {}
  template <std::integral T>
  constexpr mdata_2e61n1(T v) : v_(mod_(v)) {}

  constexpr raw_type val() const { return v_; }
  constexpr raw_type &data() { return v_; }
  constexpr raw_type const &data() const { return v_; }
  constexpr mdata_2e61n1 operator-() const { return MOD - v_; }
  constexpr mdata_2e61n1 &operator+=(mdata_2e61n1 const &r) {
    v_ = mod_(v_ + r.v_);
    return *this;
  }
  constexpr mdata_2e61n1 &operator-=(mdata_2e61n1 const &r) {
    v_ < r.v_ ? v_ = mod_(v_ + MOD - r.v_) : v_ -= r.v_;
    return *this;
  }
  constexpr mdata_2e61n1 &operator*=(mdata_2e61n1 const &r) {
    raw_type au = v_ >> 31, ad = v_ & _31, bu = r.v_ >> 31, bd = r.v_ & _31, _ = ad * bu + au * bd;
    v_ = mod_(((au * bu) << 1) + ad * bd + ((_ & _30) << 31) + (_ >> 30));
    return *this;
  }
};

}  // namespace tifa_libs::math

#endif