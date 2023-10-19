#ifndef TIFALIBS_POLY_POLYDATA_D3NTT
#define TIFALIBS_POLY_POLYDATA_D3NTT

#include "../conv/conv_3ntt.hpp"
#include "../conv/conv_naive.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint, class mint0, class mint1, class mint2>
struct polydata_d3ntt {
  using value_type = mint;

  vec<mint> d;

  explicit constexpr polydata_d3ntt(size_t sz = 1) : d(sz) {}
  explicit constexpr polydata_d3ntt(std::initializer_list<mint> v) : d(v) {}
  explicit constexpr polydata_d3ntt(vec<mint> const &v) : d(v) {}

  void conv(polydata_d3ntt const &r, size_t ans_size) { d = ans_size < 32 ? conv_naive(d, r.d, ans_size) : conv_3ntt<mint0, mint1, mint2>(d, r.d, ans_size); }
  void conv(polydata_d3ntt const &r) { conv(r, d.size() + r.d.size() - 1); }
};

}  // namespace tifa_libs::math

#endif