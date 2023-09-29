#ifndef TIFALIBS_POLY_POLYDATA_S
#define TIFALIBS_POLY_POLYDATA_S

#include "../util/util.hpp"

#include "conv_naive.hpp"
#include "conv_ntt.hpp"

namespace tifa_libs::math {

template <class mint>
struct polydata_s {
  static constexpr u64 MOD = mint::mod();
  static_assert(MOD > 1 && (MOD & 3) == 1, "MOD must be prime with 4k+1");

  using value_type = mint;

  vec<mint> d;

  explicit constexpr polydata_s(size_t sz = 1):
    d(std::max((size_t)1, sz)) {}
  explicit constexpr polydata_s(vec<mint> const &v):
    d(v) {}

  void conv(polydata_s const &r, size_t ans_size) { d = d.size() + r.d.size() < 64 ? conv_naive(d, r.d, ans_size) : conv_ntt(d, r.d, ans_size); }
  void conv(polydata_s const &r) { conv(r, d.size() + r.size() - 1); }
};

}  // namespace tifa_libs::math

#endif