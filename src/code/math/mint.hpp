#ifndef TIFALIBS_MATH_MINT
#define TIFALIBS_MATH_MINT

#include "../nt/inverse.hpp"
#include "../util/traits.hpp"

namespace tifa_libs::math {

template <template <u64 Arg> class D, u64 Arg = 998244353>
struct mint : D<Arg> {
  using base_t = D<Arg>;

  CEXP mint() = default;
  CEXP mint(int_c auto v) NE : base_t(v) {}

  using raw_t = base_t::raw_t;
  using sraw_t = to_sint_t<raw_t>;
  static CEXP raw_t mod() NE { return base_t::mod(); }
  static CEXP sraw_t smod() NE { return (sraw_t)base_t::mod(); }
  CEXP raw_t val() CNE { return base_t::val(); }
  CEXP sraw_t sval() CNE { return (sraw_t)base_t::val(); }
  CEXP raw_t &data() NE { return base_t::data(); }
  template <int_c T>
  CEXPE operator T() CNE { return (T)val(); }
  CEXP mint &operator+=(mint CR r) NE {
    mint::add(r);
    return *this;
  }
  CEXP mint &operator-=(mint CR r) NE {
    mint::sub(r);
    return *this;
  }
  CEXP mint &operator*=(mint CR r) NE {
    mint::mul(r);
    return *this;
  }
  CEXP mint &operator/=(mint CR r) NE { return *this = *this * r.inv(); }
  CEXP mint CR operator+() CNE { return *this; }
  CEXP mint operator-() CNE { return base_t::template neg<mint>(); }
  CEXP mint inv() CNE { return inverse(val(), mod()); }
  friend CEXP mint operator+(mint l, mint CR r) NE { return l += r; }
  friend CEXP mint operator-(mint l, mint CR r) NE { return l -= r; }
  friend CEXP mint operator*(mint l, mint CR r) NE { return l *= r; }
  friend CEXP mint operator/(mint l, mint CR r) NE { return l /= r; }
  friend CEXP bool operator==(mint CR l, mint CR r) NE { return l.val() == r.val(); }
  friend CEXP auto operator<=>(mint CR l, mint CR r) NE { return l.sval() - r.sval(); }
  friend auto &operator>>(istream_c auto &is, mint &x) NE {
    i64 _;
    is >> _, x = mint(_);
    return is;
  }
  friend auto &operator<<(ostream_c auto &os, mint CR x) NE { return os << x.val(); }
  friend CEXP auto abs(mint CR x) NE { return x.val(); }
};

}  // namespace tifa_libs::math

#endif