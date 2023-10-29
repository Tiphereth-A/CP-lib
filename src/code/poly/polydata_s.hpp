#ifndef TIFALIBS_POLY_POLYDATA_S
#define TIFALIBS_POLY_POLYDATA_S

#include "../conv/conv_naive.hpp"
#include "../conv/conv_ntt.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint>
struct polydata_s {
  static_assert(mint::mod() > 1 && (mint::mod() & 3) == 1, "MOD must be prime with 4k+1");

  using value_type = mint;

  vec<mint> d;

  explicit constexpr polydata_s(usz sz = 1, value_type const &val = value_type{}) : d(sz, val) {}
  constexpr polydata_s(typename vec<mint>::const_iterator begin, typename vec<mint>::const_iterator end) : d(begin, end) {}
  explicit constexpr polydata_s(std::initializer_list<mint> v) : d(v) {}
  explicit constexpr polydata_s(vec<mint> const &v) : d(v) {}

  void conv(polydata_s const &r, usz ans_size) { d = ans_size < 32 ? conv_naive(d, r.d, ans_size) : conv_ntt(d, r.d, ans_size); }
  void conv(polydata_s const &r) { conv(r, d.size() + r.d.size() - 1); }
};

}  // namespace tifa_libs::math

#endif