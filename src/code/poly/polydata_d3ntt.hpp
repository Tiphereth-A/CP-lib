#ifndef TIFALIBS_POLY_POLYDATA_D3NTT
#define TIFALIBS_POLY_POLYDATA_D3NTT

#include "../conv/conv_3ntt.hpp"
#include "../conv/conv_naive.hpp"
#include "../util/util.hpp"
#include "polydata_convtype.hpp"

namespace tifa_libs::math {

template <class mint, class mint0, class mint1, class mint2>
struct polydata_d3ntt {
  using value_type = mint;
  using conv_core = std::tuple<NTT<mint0>, NTT<mint1>, NTT<mint2>>;
  static constexpr auto ccore_type = pdct_NTT3;

  vec<mint> d;
  static inline conv_core ccore;

  explicit constexpr polydata_d3ntt(u32 sz = 1, value_type const &val = value_type{}) : d(sz, val) {}
  constexpr polydata_d3ntt(typename vec<mint>::const_iterator begin, typename vec<mint>::const_iterator end) : d(begin, end) {}
  explicit constexpr polydata_d3ntt(std::initializer_list<mint> v) : d(v) {}
  explicit constexpr polydata_d3ntt(vec<mint> const &v) : d(v) {}

  void conv(polydata_d3ntt const &r, u32 ans_size) { d = ans_size < 32 ? conv_naive(d, r.d, ans_size) : conv_3ntt(ccore, d, r.d, ans_size); }
  void conv(polydata_d3ntt const &r) { conv(r, u32(d.size() + r.d.size() - 1)); }
};

}  // namespace tifa_libs::math

#endif