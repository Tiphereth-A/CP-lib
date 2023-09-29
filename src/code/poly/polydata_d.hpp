#ifndef TIFALIBS_POLY_POLYDATA_D
#define TIFALIBS_POLY_POLYDATA_D

#include "../util/util.hpp"

#include "conv_mtt.hpp"
#include "conv_naive.hpp"

namespace tifa_libs::math {

template <class mint>
struct polydata_d {
  static constexpr u64 MOD = mint::mod();
  static_assert(MOD > 1);

  using value_type = mint;

  vec<mint> d;

  explicit constexpr polydata_d(size_t sz = 1):
    d(std::max((size_t)1, sz)) {}
  explicit constexpr polydata_d(vec<mint> const &v):
    d(v) {}

  void conv(polydata_d const &r, size_t ans_size) { d = d.size() + r.d.size() < 64 ? conv_naive(d, r.d, ans_size) : conv_mtt(d, r.d, ans_size); }
  void conv(polydata_d const &r) { conv(r, d.size() + r.size() - 1); }
};

}  // namespace tifa_libs::math

#endif