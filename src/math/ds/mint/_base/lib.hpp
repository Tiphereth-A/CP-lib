#pragma once

#include "../../../../nt/inverse/lib.hpp"
#include "../../../../util/traits/others/lib.hpp"

namespace tifa_libs::mint_impl_ {

struct mint_tag_base {};
template <std::derived_from<mint_tag_base> tag_t>
struct mint : tag_t {
  CEXP mint() = default;
  CEXP mint(int_c auto v) NE : tag_t(v) {}

  using raw_t = tag_t::raw_t;
  using sraw_t = to_sint_t<raw_t>;
  static CEXP sraw_t smod() NE { return (sraw_t)tag_t::mod(); }
  CEXP sraw_t sval() CNE { return (sraw_t)tag_t::val(); }
  template <int_c T>
  CEXPE operator T() CNE { return (T)tag_t::val(); }
  CEXP mint& operator+=(mint CR r) NE {
    mint::add(r);
    return *this;
  }
  CEXP mint& operator-=(mint CR r) NE {
    mint::sub(r);
    return *this;
  }
  CEXP mint& operator*=(mint CR r) NE {
    mint::mul(r);
    return *this;
  }
  CEXP mint& operator/=(mint CR r) NE { return *this = *this * r.inv(); }
  CEXP mint CR operator+() CNE { return *this; }
  CEXP mint operator-() CNE { return tag_t::template neg<mint>(); }
  CEXP mint inv() CNE { return inverse(tag_t::val(), tag_t::mod()); }
  friend CEXP mint operator+(mint l, mint CR r) NE { return l += r; }
  friend CEXP mint operator-(mint l, mint CR r) NE { return l -= r; }
  friend CEXP mint operator*(mint l, mint CR r) NE { return l *= r; }
  friend CEXP mint operator/(mint l, mint CR r) NE { return l /= r; }
  friend CEXP bool operator==(mint CR l, mint CR r) NE { return l.val() == r.val(); }
  friend CEXP auto operator<=>(mint CR l, mint CR r) NE { return l.sval() <=> r.sval(); }
  friend auto& operator>>(istream_c auto& is, mint& x) NE {
    i64 _;
    is >> _, x = mint(_);
    return is;
  }
  friend auto& operator<<(ostream_c auto& os, mint CR x) NE { return os << x.val(); }
  friend CEXP auto abs(mint CR x) NE { return x.val(); }
};

}  // namespace tifa_libs::mint_impl_
