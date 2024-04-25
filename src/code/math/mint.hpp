#ifndef TIFALIBS_MATH_MINT
#define TIFALIBS_MATH_MINT

#include "../nt/inverse.hpp"
#include "../util/traits.hpp"

namespace tifa_libs::math {

template <class D, uint_c Rt>
class mint {
  CEXP D CR d() const { return static_cast<D CR>(*this); }
  CEXP D &d() { return static_cast<D &>(*this); }

 protected:
  Rt v_{};

 public:
  CEXP mint() {}
  template <int_c T>
  CEXP mint(T v) : v_(D::mod_(v)) {}
  CEXP operator D() { return d(); }

  using raw_type = Rt;
  using sraw_type = to_sint_t<Rt>;
  static CEXP raw_type mod() { return D::mod_(); }
  static CEXP sraw_type smod() { return (sraw_type)D::mod_(); }
  CEXP raw_type val() const { return d().val_(); }
  CEXP sraw_type sval() const { return (sraw_type)d().val_(); }
  CEXP raw_type &data() { return d().data_(); }

  template <int_c T>
  explicit CEXP operator T() const { return (T)val(); }
  CEXP mint &operator+=(mint CR r) { return d().adde_(r.d()); }
  CEXP mint &operator-=(mint CR r) { return d().sube_(r.d()); }
  CEXP mint &operator*=(mint CR r) { return d().mule_(r.d()); }
  CEXP mint &operator/=(mint CR r) { return *this = *this * r.inv(); }
  CEXP mint CR operator+() const { return *this; }
  CEXP mint operator-() const { return d().neg_(); }
  CEXP mint inv() const { return inverse(val(), mod()); }
  friend CEXP mint operator+(mint l, mint CR r) { return l += r; }
  friend CEXP mint operator-(mint l, mint CR r) { return l -= r; }
  friend CEXP mint operator*(mint l, mint CR r) { return l *= r; }
  friend CEXP mint operator/(mint l, mint CR r) { return l /= r; }
  friend CEXP bool operator==(mint CR l, mint CR r) { return l.val() == r.val(); }
  friend CEXP auto operator<=>(mint CR l, mint CR r) { return l.sval() - r.sval(); }
  friend std::istream &operator>>(std::istream &is, mint &x) {
    i64 _;
    is >> _;
    x = mint(_);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint CR x) { return os << x.val(); }
  friend CEXP mint abs(mint CR x) { return x.val(); }
};

}  // namespace tifa_libs::math

#endif