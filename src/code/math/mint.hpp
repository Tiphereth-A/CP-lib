#ifndef TIFALIBS_MATH_MINT
#define TIFALIBS_MATH_MINT

#include "inverse.hpp"

namespace tifa_libs::math {

template <class MDATA>
class mint {
  MDATA d;

 public:
  using raw_type = typename MDATA::raw_type;
  using sraw_type = typename MDATA::sraw_type;
  static constexpr raw_type mod() { return MDATA::mod(); }
  static constexpr sraw_type smod() { return MDATA::smod(); }

  constexpr mint() : d(0) {}
  constexpr mint(MDATA const &d) : d(d) {}
  template <std::signed_integral T>
  constexpr mint(T v) : d(v) {}
  template <std::unsigned_integral T>
  constexpr mint(T v) : d(v) {}

  constexpr raw_type val() const { return d.val(); }
  constexpr sraw_type sval() const { return d.sval(); }
  constexpr raw_type &data() { return d.data(); }
  template <std::integral T>
  explicit constexpr operator T() const { return (T)(d.val()); }
  constexpr mint &operator+=(mint const &r) {
    d += r.d;
    return *this;
  }
  constexpr mint &operator-=(mint const &r) {
    d -= r.d;
    return *this;
  }
  constexpr mint &operator*=(mint const &r) {
    d *= r.d;
    return *this;
  }
  constexpr mint &operator/=(mint const &r) { return *this = *this * r.inv(); }
  constexpr mint const &operator+() const { return *this; }
  constexpr mint operator-() const { return -d; }
  constexpr mint inv() const { return inverse(val(), mod()); }
  friend constexpr mint operator+(mint l, mint const &r) { return l += r; }
  friend constexpr mint operator-(mint l, mint const &r) { return l -= r; }
  friend constexpr mint operator*(mint l, mint const &r) { return l *= r; }
  friend constexpr mint operator/(mint l, mint const &r) { return l /= r; }
  friend constexpr bool operator==(mint const &l, mint const &r) { return l.val() == r.val(); }
  friend constexpr auto operator<=>(mint const &l, mint const &r) { return l.sval() - r.sval(); }
  friend std::istream &operator>>(std::istream &is, mint &x) {
    i64 _;
    is >> _;
    x = mint(_);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint const &x) { return os << x.val(); }
  friend constexpr mint abs(mint const &x) { return x.val(); }
};

}  // namespace tifa_libs::math

#endif