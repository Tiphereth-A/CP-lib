#ifndef TIFALIBS_MATH_MINT
#define TIFALIBS_MATH_MINT

#include "../nt/inverse.hpp"
#include "../util/traits.hpp"

namespace tifa_libs::math {

template <template <u64 Arg> class D, u64 Arg = 998244353>
struct mint : D<Arg> {
  using base_t = D<Arg>;

  CEXP mint() : base_t() {}
  CEXP mint(int_c auto v) : base_t(v) {}

  using raw_t = base_t::raw_t;
  using sraw_t = to_sint_t<raw_t>;
  static CEXP raw_t mod() { return base_t::mod(); }
  static CEXP sraw_t smod() { return (sraw_t)base_t::mod(); }
  CEXP raw_t val() const { return base_t::val(); }
  CEXP sraw_t sval() const { return (sraw_t)base_t::val(); }
  CEXP raw_t &data() { return base_t::data(); }
  template <int_c T>
  CEXPE operator T() const { return (T)val(); }
  CEXP mint &operator+=(mint CR r) { return mint::add(r), *this; }
  CEXP mint &operator-=(mint CR r) { return mint::sub(r), *this; }
  CEXP mint &operator*=(mint CR r) { return mint::mul(r), *this; }
  CEXP mint &operator/=(mint CR r) { return *this = *this * r.inv(); }
  CEXP mint CR operator+() const { return *this; }
  CEXP mint operator-() const { return base_t::template neg<mint>(); }
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
  friend CEXP auto abs(mint CR x) { return x.val(); }
};

}  // namespace tifa_libs::math

#endif