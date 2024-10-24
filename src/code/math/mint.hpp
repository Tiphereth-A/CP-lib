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

  using raw_t = Rt;
  using sraw_t = to_sint_t<Rt>;
  static CEXP raw_t mod() { return D::mod_(); }
  static CEXP sraw_t smod() { return (sraw_t)D::mod_(); }
  CEXP raw_t val() const { return d().val_(); }
  CEXP sraw_t sval() const { return (sraw_t)d().val_(); }
  CEXP raw_t &data() { return d().data_(); }
  template <int_c T>
  CEXPE operator T() const { return (T)val(); }
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
    return is >> _, x = mint(_), is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint CR x) { return os << x.val(); }
  friend CEXP mint abs(mint CR x) { return x.val(); }
};

}  // namespace tifa_libs::math

#endif