#ifndef TIFALIBS_POLY_POLYDATA_D
#define TIFALIBS_POLY_POLYDATA_D

#include "../conv/conv_mtt.hpp"
#include "../conv/conv_naive.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint>
struct polydata_d {
  using value_type = mint;

  vec<mint> d;

  explicit constexpr polydata_d(usz sz = 1) : d(sz) {}
  explicit constexpr polydata_d(std::initializer_list<mint> v) : d(v) {}
  explicit constexpr polydata_d(vec<mint> const &v) : d(v) {}

  void conv(polydata_d const &r, usz ans_size) { d = ans_size < 32 ? conv_naive(d, r.d, ans_size) : conv_mtt(d, r.d, ans_size); }
  void conv(polydata_d const &r) { conv(r, d.size() + r.d.size() - 1); }
};

}  // namespace tifa_libs::math

#endif