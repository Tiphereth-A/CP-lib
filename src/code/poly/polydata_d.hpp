#ifndef TIFALIBS_POLY_POLYDATA_D
#define TIFALIBS_POLY_POLYDATA_D

#include "../conv/conv_mtt.hpp"
#include "../conv/conv_naive.hpp"
#include "../util/util.hpp"
#include "polydata_convtype.hpp"

namespace tifa_libs::math {

template <class mint, class FP = f64>
struct polydata_d {
  using value_type = mint;
  using conv_core = FFT<FP>;
  static constexpr auto ccore_type = pdct_FFT;

  vec<mint> d;
  static conv_core ccore;

  explicit constexpr polydata_d(u32 sz = 1, value_type const &val = value_type{}) : d(sz, val) {}
  constexpr polydata_d(typename vec<mint>::const_iterator begin, typename vec<mint>::const_iterator end) : d(begin, end) {}
  explicit constexpr polydata_d(std::initializer_list<mint> v) : d(v) {}
  explicit constexpr polydata_d(vec<mint> const &v) : d(v) {}

  void conv(polydata_d const &r, u32 ans_size) { d = ans_size < 32 ? conv_naive(d, r.d, ans_size) : conv_mtt(ccore, d, r.d, ans_size); }
  void conv(polydata_d const &r) { conv(r, u32(d.size() + r.d.size() - 1)); }
};

}  // namespace tifa_libs::math

#endif