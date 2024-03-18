#ifndef TIFALIBS_MATH_MINT
#define TIFALIBS_MATH_MINT

#include "../nt/inverse.hpp"
#include "../util/traits.hpp"

namespace tifa_libs::math {

template <class D, uint_c Rt>
class mint {
  constexpr D const &d() const { return static_cast<D const &>(*this); }
  constexpr D &d() { return static_cast<D &>(*this); }

 protected:
  Rt v_{};

 public:
  constexpr mint() {}
  template <int_c T>
  constexpr mint(T v) : v_(D::mod_(v)) {}
  constexpr operator D() { return d(); }

  using raw_type = Rt;
  using sraw_type = to_sint_t<Rt>;
  static constexpr raw_type mod() { return D::mod_(); }
  static constexpr sraw_type smod() { return (sraw_type)D::mod_(); }
  constexpr raw_type val() const { return d().val_(); }
  constexpr sraw_type sval() const { return (sraw_type)d().val_(); }
  constexpr raw_type &data() { return d().data_(); }

  template <int_c T>
  explicit constexpr operator T() const { return (T)val(); }
  constexpr mint &operator+=(mint const &r) { return d().adde_(r.d()); }
  constexpr mint &operator-=(mint const &r) { return d().sube_(r.d()); }
  constexpr mint &operator*=(mint const &r) { return d().mule_(r.d()); }
  constexpr mint &operator/=(mint const &r) { return *this = *this * r.inv(); }
  constexpr mint const &operator+() const { return *this; }
  constexpr mint operator-() const { return d().neg_(); }
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